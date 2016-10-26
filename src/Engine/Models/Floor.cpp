//
// Created by invander on 24.10.16.
//

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Floor.h"

using namespace Models;

Floor::Floor(GLuint program, float width, float length, float height)
		: Model(program), mWidth(width), mLength(length), mHeight(height)
{
	// Bind attributes
	bindAttrib(mProgram, mAttrCoord3d, "coord3d");

	// Bind uniforms
	bindUniform(mProgram, mUniMvp, "mvp");

	// Prepare buffer of vertices
	const GLfloat vertices[] = {
			-1.0f * width,	height,	1.0f * length,
			1.0f * width,	height,	1.0f * length,
			1.0f * width,	height,	-1.0f * length,
			-1.0f * width,	height,	-1.0f * length,
	};

	glGenBuffers(1, &mVboVertices);
	glBindBuffer(GL_ARRAY_BUFFER, mVboVertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

Floor::~Floor()
{
	glDeleteBuffers(1, &mVboVertices);
}

void Floor::draw(const glm::mat4 &view)
{
	// Move object to location
	glm::mat4 mvp = glm::translate(view, mPosition);
	glUniformMatrix4fv(mUniMvp, 1, GL_FALSE, glm::value_ptr(mvp));

	// Draw it
	glBindBuffer(GL_ARRAY_BUFFER, mVboVertices);
	glEnableVertexAttribArray((GLuint)mAttrCoord3d);
	glVertexAttribPointer(
			(GLuint)mAttrCoord3d, // attribute
			3, // number of elements per vertex
			GL_FLOAT, // type of element
			GL_FALSE, // take value as-is
			0, // next data appears every 5 floats
			0); // offset of first element

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDisableVertexAttribArray((GLuint)mAttrCoord3d);
}

void Floor::update() {

}
