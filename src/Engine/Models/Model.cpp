//
// Created by invander on 22.10.16.
//

#include "Model.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.inl>

Models::Model::Model(GLuint program, bool createEBO, bool createVBO, bool createVAO)
	: mProgram{program}
{
	// Bind uniforms
	bindUniform(mProgram, mMvp, "mvp");

	// Create buffers
	if (createVAO) {
		glGenVertexArrays(1, &mVAO);
	}

	if (createVBO) {
		glGenBuffers(1, &mVBO);
	}

	if (createEBO) {
		glGenBuffers(1, &mEBO);
	}
}

Models::Model::~Model() 
{
	if (mVBO != 0) {
		glDeleteBuffers(1, &mVBO);
	}

	if (mEBO != 0) {
		glDeleteBuffers(1, &mEBO);
	}

	if (mVAO != 0) {
		glDeleteBuffers(1, &mVAO);
	}
}


void Models::Model::update()
{
}

void Models::Model::draw(const glm::mat4& view)
{
	glUseProgram(mProgram);

	// Move object to location
	glm::mat4 mvp = glm::translate(view, mPosition);
	glUniformMatrix4fv(mMvp, 1, GL_FALSE, glm::value_ptr(mvp));
}
