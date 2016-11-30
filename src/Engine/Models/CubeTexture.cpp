//
// Created by invander on 24.10.16.
//

#include <cstring>
#include "CubeTexture.h"

Models::CubeTexture::CubeTexture(GLuint program, float size, GLuint texture) :
		Cube(program, size), mTextureId(texture)
{
	bindUniform(mProgram, mUniTexture, "texture");

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

	// Bing vao again
	glBindVertexArray(mVAO);

	// add new buffer
	glGenBuffers(1, &mVboTexcoords);
	glBindBuffer(GL_ARRAY_BUFFER, mVboTexcoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);

	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Models::CubeTexture::~CubeTexture()
{
	//glDeleteTextures(1, &mTextureId);
	glDeleteBuffers(1, &mVboTexcoords);
}

void Models::CubeTexture::draw(const glm::mat4& view) 
{
	Cube::draw(view);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTextureId);
	glUniform1i(mUniTexture, 0);

	glBindVertexArray(mVAO);

	int size; glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);

	glBindVertexArray(0);
}
