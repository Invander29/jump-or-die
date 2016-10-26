#include "GameObject.h"
#include <iterator>

using namespace Models;

bool GameObject::bindAttrib(GLuint program, GLint& attrib, const char* name)
{
	if ((attrib = glGetAttribLocation(program, name)) == -1) {
		Utils::error("Cannot bind attribute with name %s", name);
		return false;
	}
	return true;
}

bool GameObject::bindUniform(GLuint program, GLint& attrib, const char* name)
{
	if ((attrib = glGetUniformLocation(program, name)) == -1) {
		Utils::error("Cannot bind uniform with name %s", name);
		return false;
	}
	return true;
}
