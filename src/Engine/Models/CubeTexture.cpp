//
// Created by invander on 24.10.16.
//

#include "CubeTexture.h"

Models::CubeTexture::CubeTexture(GLuint program, float size, GLuint texture) :
		Cube(program, size), mTextureId(texture)
{
	// Bind attributes
	bindAttrib(mProgram, mAttrTexcoord, "texcoord");

	// Texture coordinates
	GLfloat texcoords[2*4*6] = {
		// front
		0.0, 0.0,
		1.0, 0.0,
		1.0, 1.0,
		0.0, 1.0,
	};
	for (int i = 1; i < 6; i++)
		memcpy(&texcoords[i * 4 * 2], &texcoords[0], 2 * 4 * sizeof(GLfloat));

	glGenBuffers(1, &mVboTexcoords);
	glBindBuffer(GL_ARRAY_BUFFER, mVboTexcoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);
}

Models::CubeTexture::~CubeTexture()
{
	//glDeleteTextures(1, &mTextureId);
	glDeleteBuffers(1, &mVboTexcoords);
}

void Models::CubeTexture::draw(const glm::mat4& view) {
	Cube::draw(view);

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

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIboElements);
	int size; glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);

	glDisableVertexAttribArray((GLuint)mAttrCoord3d);
}
