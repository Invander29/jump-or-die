//
// Created by invander on 25.10.16.
//

#include "FloorTexture.h"

Models::FloorTexture::FloorTexture(GLuint program, float width, float length, float height, GLuint texture)
		: Floor(program, width, length, height), mTextureId(texture)
{
	// Bind attributes
	bindAttrib(mProgram, mAttrTexcoord, "texcoord");

	// Texture coordinates
	GLfloat texcoords[] = {
			0.0, 0.0,
			width, 0.0,
			width, length,
			0.0, length,
	};

	glGenBuffers(1, &mVboTexcoords);
	glBindBuffer(GL_ARRAY_BUFFER, mVboTexcoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);
}

void Models::FloorTexture::draw(const glm::mat4 &view)
{
	glUseProgram(mProgram);

	glBindBuffer(GL_ARRAY_BUFFER, mVboTexcoords);
	glEnableVertexAttribArray((GLuint)mAttrTexcoord);
	glVertexAttribPointer((GLuint)mAttrTexcoord,
	                      2, // elements per vertex (x,y)
	                      GL_FLOAT, // element type
	                      GL_FALSE,
	                      0, // no extra data between each position
	                      0);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(mUniTexture, /*GL_TEXTURE*/0);
	glBindTexture(GL_TEXTURE_2D, mTextureId);

	Floor::draw(view);

	glDisableVertexAttribArray((GLuint)mAttrCoord3d);
}
