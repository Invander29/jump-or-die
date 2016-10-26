//
// Created by invander on 22.10.16.
//

#include "ShaderManager.h"
#include "../Utils/FileReader.h"
#include "../Utils/Utils.h"

using namespace std;
using namespace Managers;

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

	Utils::debug("Compiling Vertex Shader: %s", filename.c_str());
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

	Utils::debug("Compiling Fragment Shader: %s", filename.c_str());
	GLuint shaderId = createShader(mPath + filename, GL_FRAGMENT_SHADER);
	if (shaderId == 0) {
		return 0;
	}

	Shader shader(shaderId);
	mFragmentShaders[filename] = shader;
	return shader.id;
}

GLuint ShaderManager::createProgram(const std::string &name, const std::string &vs, const std::string &fs)
{
	// Check if program exists
	unordered_map<string, Program>::iterator it = mPrograms.find(name);
	if (it != mPrograms.end()) {
		it->second.counter++;
		return it->second.id;
	}

	GLuint vertex = createVertexShader(vs);
	if (vertex == 0) {
		return 0;
	}

	GLuint fragment = createFragmentShader(fs);
	if (fragment == 0) {
		return 0;
	}

	Utils::debug("Linking Program: %s", name.c_str());
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertex);
	glAttachShader(programId, fragment);
	glLinkProgram(programId);

	GLint linkOk = GL_FALSE;
	glGetProgramiv(programId, GL_LINK_STATUS, &linkOk);
	if (!linkOk) {
		Utils::errorGL(programId, "Cannot link programId!");
		return 0;
	}

	Program program(programId, vs, fs);
	mPrograms[name] = program;
	return program.id;
}

GLuint ShaderManager::createShader(const std::string &filename, GLenum type) {
	Utils::FileReader fileReader;
	std::string content = fileReader.readFile(filename);
	if (content.empty()) {
		Utils::error("Cannot open file %s", filename.c_str());
		return 0;
	}

	GLuint result = glCreateShader(type);
	const char* shaderContent = content.c_str();
	glShaderSource(result, 1, &shaderContent, nullptr);

	GLint compileOK = GL_FALSE;
	glCompileShader(result);
	glGetShaderiv(result, GL_COMPILE_STATUS, &compileOK);
	if (!compileOK) {
		Utils::errorGL(result, "Cannot compile shader %s", filename.c_str());
		glDeleteShader(result);
		return 0;
	}

	return result;
}

bool ShaderManager::deleteVertexShader(const std::string &filename) {
	unordered_map<string, Shader>::const_iterator it = mVertexShaders.find(filename);
	if (it == mVertexShaders.end()) {
		Utils::error("Cannot delete vertex shader, shader \"%s\" not found!", filename.c_str());
		return false;
	}

	glDeleteShader(it->second.id);
	mVertexShaders.erase(it);
	return true;
}

bool ShaderManager::deleteFragmentShader(const std::string &filename) {
	unordered_map<string, Shader>::const_iterator it = mFragmentShaders.find(filename);
	if (it == mFragmentShaders.end()) {
		Utils::error("Cannot delete fragment shader, shader \"%s\" not found!", filename.c_str());
		return false;
	}

	glDeleteShader(it->second.id);
	mFragmentShaders.erase(it);
	return true;
}

bool ShaderManager::deleteProgram(const std::string &filename) {
	unordered_map<string, Program>::const_iterator it = mPrograms.find(filename);
	if (it == mPrograms.end()) {
		Utils::error("Cannot delete program, program \"%s\" not found!", filename.c_str());
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
