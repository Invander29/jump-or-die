//
// Created by invander on 24.10.16.
//

#include "CubeColor.h"

Models::CubeColor::CubeColor(GLuint program, float size, float r, float g, float b)
		: Cube(program, size), mR(r), mG(g), mB(b)
{
	bindUniform(mProgram, mUniColor, "v_color");
}

Models::CubeColor::~CubeColor()
{
}

void Models::CubeColor::draw(const glm::mat4& view) {

	glUniform3f(mUniColor, mR, mG, mB);
	Cube::draw(view);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIboElements);
	int size; glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
}
