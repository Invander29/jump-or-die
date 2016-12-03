#include "GameObject.h"

#include "../Application.h"
#include "../Utils/Message.h"

using namespace Models;
using namespace Utils;


GLint& GameObject::Uniform::operator()()
{ 
	return this->operator[](Application::instance().lightingMode());
}

bool GameObject::bindAttrib(GLuint program, GLint& attrib, const char* name)
{
	if ((attrib = glGetAttribLocation(program, name)) == -1) {
		Message::error(__FILE__, __LINE__, "Cannot bind attribute with name %s", name);
		return false;
	}
	return true;
}

bool GameObject::bindUniform(GLuint program, GLint& attrib, const char* name)
{
	if ((attrib = glGetUniformLocation(program, name)) == -1) {
		Message::error("bind", __LINE__, "Cannot bind uniform to program %d with name %s", program, name);
		return false;
	}
	return true;
}

bool GameObject::bindUniform(std::shared_ptr<Managers::ShaderManager::Program> program, Uniform& uniform, const char* name)
{
	bool result = true;
	GLuint programId = 0;

	for (Lighting::Type type : {Lighting::Type::NONE, Lighting::Type::PHONG}) {
		if ((programId = program->id(type)) != 0) {
			if (!bindUniform(programId, uniform[type], name)) {
				result = false;
			}
		}
	}

	return result;
}

bool GameObject::bindUniform(Lighting::Type type, std::shared_ptr<Managers::ShaderManager::Program> program, Uniform& uniform, const char* name)
{
	bool result = true;
	GLuint programId = 0;

	if ((programId = program->id(type)) != 0) {
		if (!bindUniform(programId, uniform[type], name)) {
			result = false;
		}
	}

	return result;
}