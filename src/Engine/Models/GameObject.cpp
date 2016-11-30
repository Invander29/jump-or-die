#include "GameObject.h"

#include "../Utils/Message.h"

using namespace Models;
using namespace Utils;

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
		Message::error(__FILE__, __LINE__, "Cannot bind uniform with name %s", name);
		return false;
	}
	return true;
}
