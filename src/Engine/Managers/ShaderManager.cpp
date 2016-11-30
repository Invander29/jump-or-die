//
// Created by invander on 22.10.16.
//

#include "ShaderManager.h"
#include "../Utils/FileReader.h"
#include "../Utils/Message.h"

using namespace std;
using namespace Managers;
using namespace Utils;

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

ShaderManager::Program& ShaderManager::get(const std::string &name, const std::string &vs, const std::string &fs)
{
	static Program nullProgram;

	// Check if program exists
	unordered_map<string, Program>::iterator it = mPrograms.find(name);
	if (it != mPrograms.end()) {
		it->second.counter++;
		return it->second;
	}

	GLuint vertex = createVertexShader(vs);
	if (vertex == 0) {
		return nullProgram;
	}

	GLuint fragment = createFragmentShader(fs);
	if (fragment == 0) {
		return nullProgram;
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
		return nullProgram;
	}

	Program program(programId, name, vs, fs);
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
	unordered_map<string, Program>::const_iterator it = mPrograms.find(filename);
	if (it == mPrograms.end()) {
		Message::error(__FILE__, __LINE__, "Cannot delete program, program \"%s\" not found!", filename.c_str());
		return false;
	}

	// TODO Delete only if count is zero??

	// Delete shaders
	deleteFragmentShader(it->second.fragmentShader);
	deleteVertexShader(it->second.vertexShader);

	// Delete program
	glDeleteProgram(it->second.id);
	mPrograms.erase(it);
	return true;
}

bool ShaderManager::remove(const Program& program)
{
	if (program.id == 0) {
		return false;
	}

	return remove(program.name);
}

void ShaderManager::clearVertexShaders() {
	unordered_map<string, Shader>::const_iterator it;

	for (it = mVertexShaders.begin(); it != mVertexShaders.end(); ++it) {
		glDeleteShader(it->second.id);
	}

	mVertexShaders.clear();
}

void ShaderManager::clearFragmentShaders() {
	unordered_map<string, Shader>::const_iterator it;

	for (it = mFragmentShaders.begin(); it != mFragmentShaders.end(); ++it) {
		glDeleteShader(it->second.id);
	}

	mFragmentShaders.clear();
}

void ShaderManager::clearPrograms() {
	unordered_map<string, Program>::const_iterator it;

	for (it = mPrograms.begin(); it != mPrograms.end(); ++it) {
		glDeleteShader(it->second.id);
	}

	mPrograms.clear();
}
