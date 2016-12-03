//
// Created by invander on 25.10.16.
//

#include "FloorTexture.h"
#include "../Application.h"

Models::FloorTexture::FloorTexture(std::shared_ptr<Managers::ShaderManager::Program> program, float width, float length, float height, GLuint texture)
		: Floor(program, width, length, height), mTextureId(texture)
{
	bindUniform(mProgram, mUniTexture, "texture");

	// Texture coordinates
	GLfloat texcoords[] = {
			0.0, 0.0,
			width, 0.0,
			width, length,
			0.0, length,
	};

	// Bing vao again
	glBindVertexArray(mVAO);

	// add new buffer
	glGenBuffers(1, &mVboTexcoords);
	glBindBuffer(GL_ARRAY_BUFFER, mVboTexcoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);

	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(2);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


Models::FloorTexture::~FloorTexture()
{
	glDeleteBuffers(1, &mVboTexcoords);
}

void Models::FloorTexture::draw(Scenes::Scene* scene)
{
	Floor::draw(scene);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTextureId);
	glUniform1i(mUniTexture(), 0);

	glBindVertexArray(mVAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindVertexArray(0);
}
