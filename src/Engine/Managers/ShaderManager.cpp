//
// Created by invander on 22.10.16.
//

#include "ShaderManager.h"
#include "../Utils/FileReader.h"
#include "../Utils/Message.h"
#include "../Application.h"

using namespace std;
using namespace Managers;
using namespace Utils;


ShaderManager::ProgramPart::~ProgramPart()
{
	if (mId != 0) {
		// Remove from shader manager on delete
		ShaderManager& shaderManager = Application::instance().shaderManager();
		shaderManager.deleteVertexShader(vertexShader());
		shaderManager.deleteFragmentShader(fragmentShader());
		glDeleteProgram(id());
	}
}

GLuint ShaderManager::Program::id() const
{
	return id(Application::instance().lightingMode());
}

GLuint ShaderManager::Program::id(Lighting::Type type) const
{
	std::shared_ptr<ProgramPart> part;

	switch (type) {
	case Lighting::Type::NONE:	part = mWithoutLight; break;
	case Lighting::Type::PHONG: part = mPhong; break;
	default: break;
	}

	return (part == nullptr) ? mWithoutLight->id() : part->id();
}

ShaderManager::ShaderManager(const std::string& path)
		: mPath(path)
{
}

ShaderManager::~ShaderManager() {
	clearVertexShaders();
	clearFragmentShaders();
	clearPrograms();
}

GLuint ShaderManager::createVertexShader(const std::string &filename)
{
	unordered_map<string, Shader>::iterator it = mVertexShaders.find(filename);
	if (it != mVertexShaders.end()) {
		it->second.counter++;
		return it->second.id;
	}

	Message::debug("Compiling Vertex Shader: %s", filename.c_str());
	GLuint shaderId = createShader(mPath + filename, GL_VERTEX_SHADER);
	if (shaderId == 0) {
		return 0;
	}

	Shader shader(shaderId);
	mVertexShaders[filename] = shader;
	return shader.id;
}

GLuint ShaderManager::createFragmentShader(const std::string &filename)
{
	unordered_map<string, Shader>::iterator it = mFragmentShaders.find(filename);
	if (it != mFragmentShaders.end()) {
		it->second.counter++;
		return it->second.id;
	}

	Message::debug("Compiling Fragment Shader: %s", filename.c_str());
	GLuint shaderId = createShader(mPath + filename, GL_FRAGMENT_SHADER);
	if (shaderId == 0) {
		return 0;
	}

	Shader shader(shaderId);
	mFragmentShaders[filename] = shader;
	return shader.id;
}

std::shared_ptr<ShaderManager::ProgramPart> ShaderManager::createProgram(const std::string& name, const std::string& vs, const std::string& fs)
{
	GLuint vertex = createVertexShader(vs);
	if (vertex == 0) {
		return nullptr;
	}

	GLuint fragment = createFragmentShader(fs);
	if (fragment == 0) {
		return nullptr;
	}

	Message::debug("Linking Program: %s", name.c_str());
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertex);
	glAttachShader(programId, fragment);
	glLinkProgram(programId);

	GLint linkOk = GL_FALSE;
	glGetProgramiv(programId, GL_LINK_STATUS, &linkOk);
	if (!linkOk) {
		Message::errorGL(__FILE__, __LINE__, programId, "Cannot link programId!");
		return nullptr;
	}

	return make_shared<ProgramPart>(programId, vertex, fragment, vs, fs);
}

std::shared_ptr<ShaderManager::Program> ShaderManager::get(const std::string &name, const std::string &vs, const std::string &fs)
{
	// Check if program exists
	unordered_map<string, std::shared_ptr<Program>>::iterator it = mPrograms.find(name);
	if (it != mPrograms.end()) {
		//it->second.mCounter++; NOT USED YET
		return it->second;
	}

	std::shared_ptr<Program> program = std::make_shared<Program>(name);
	std::shared_ptr<ProgramPart> part;

	// Program without lighting
	if ((part = createProgram(name, vs + ".vs", fs + ".fs")) == nullptr) {
		Message::error(__FILE__, __LINE__, "Cannot create program without lighting! %s", name.c_str());
		return nullptr;
	}
	program->mWithoutLight = part;

	// Program with phong lighting
	if ((part = createProgram(name + "_phong", vs + "_phong.vs", fs + "_phong.fs")) == nullptr) {
		Message::error(__FILE__, __LINE__, "Cannot create program with phong lighting! %s", name.c_str());
	}
	program->mPhong = part;
	
	mPrograms[name] = program;
	return mPrograms[name];
}

GLuint ShaderManager::createShader(const std::string &filename, GLenum type) {
	Utils::FileReader fileReader;
	std::string content = fileReader.readFile(filename);
	if (content.empty()) {
		Message::error(__FILE__, __LINE__, "Cannot open file %s", filename.c_str());
		return 0;
	}

	GLuint result = glCreateShader(type);
	const char* shaderContent = content.c_str();
	glShaderSource(result, 1, &shaderContent, nullptr);

	GLint compileOK = GL_FALSE;
	glCompileShader(result);
	glGetShaderiv(result, GL_COMPILE_STATUS, &compileOK);
	if (!compileOK) {
		Message::errorGL(__FILE__, __LINE__, result, "Cannot compile shader %s", filename.c_str());
		glDeleteShader(result);
		return 0;
	}

	return result;
}

bool ShaderManager::deleteVertexShader(const std::string &filename) {
	unordered_map<string, Shader>::const_iterator it = mVertexShaders.find(filename);
	if (it == mVertexShaders.end()) {
		Message::error(__FILE__, __LINE__, "Cannot delete vertex shader, shader \"%s\" not found!", filename.c_str());
		return false;
	}

	glDeleteShader(it->second.id);
	mVertexShaders.erase(it);
	return true;
}

bool ShaderManager::deleteFragmentShader(const std::string &filename) {
	unordered_map<string, Shader>::const_iterator it = mFragmentShaders.find(filename);
	if (it == mFragmentShaders.end()) {
		Message::error(__FILE__, __LINE__, "Cannot delete fragment shader, shader \"%s\" not found!", filename.c_str());
		return false;
	}

	glDeleteShader(it->second.id);
	mFragmentShaders.erase(it);
	return true;
}

bool ShaderManager::remove(const std::string &filename) {
	unordered_map<string, std::shared_ptr<Program>>::const_iterator it = mPrograms.find(filename);
	if (it == mPrograms.end()) {
		Message::error(__FILE__, __LINE__, "Cannot delete program, program \"%s\" not found!", filename.c_str());
		return false;
	}

	// TODO Delete only if count is zero??
	// Delete program and it's shaders
	mPrograms.erase(it);
	return true;
}

bool ShaderManager::remove(const Program& program)
{
	return remove(program.name());
}

void ShaderManager::clearVertexShaders() 
{
	unordered_map<string, Shader>::const_iterator it;

	for (it = mVertexShaders.begin(); it != mVertexShaders.end(); ++it) {
		glDeleteShader(it->second.id);
	}

	mVertexShaders.clear();
}

void ShaderManager::clearFragmentShaders() 
{
	unordered_map<string, Shader>::const_iterator it;

	for (it = mFragmentShaders.begin(); it != mFragmentShaders.end(); ++it) {
		glDeleteShader(it->second.id);
	}

	mFragmentShaders.clear();
}

void ShaderManager::clearPrograms() 
{
	mPrograms.clear();
}
