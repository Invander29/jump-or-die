//
// Created by invander on 22.10.16.
//

#include "ModelObject.h"

#include <gl/gl3w.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Application.h"
#include "../Scenes/Scene.h"

Models::ModelObject::ModelObject(std::shared_ptr<Managers::ShaderManager::Program> program, bool createEBO, bool createVBO, bool createVAO, bool createNBO)
	: mProgram{program}
{
	// Bind uniforms
	bindUniform(mProgram, mUniView, "view");
	bindUniform(mProgram, mUniModel, "model");

	bindUniform(Lighting::Type::PHONG, mProgram, mUniLightPos, "lightPos");
	bindUniform(Lighting::Type::PHONG, mProgram, mUniLightColor, "lightColor");
	bindUniform(Lighting::Type::PHONG, mProgram, mUniViewPosition, "viewPos");

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

	if (createNBO) {
		glGenBuffers(1, &mNBO);
	}
}

Models::ModelObject::~ModelObject() 
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

	if (mNBO != 0) {
		glDeleteBuffers(1, &mNBO);
	}
}


void Models::ModelObject::update()
{
}

void Models::ModelObject::draw(Scenes::Scene* scene)
{
	glUseProgram(mProgram->id());

	// Set light and camera options
	glUniform3fv(mUniLightPos(), 1, glm::value_ptr(scene->light().position()));
	glUniform3fv(mUniLightColor(), 1, glm::value_ptr(scene->light().color()));
	glUniform3fv(mUniViewPosition(), 1, glm::value_ptr(scene->camera().position()));

	glm::mat4 model = glm::scale(glm::translate(glm::mat4(1.0f), mPosition), mScale);
	model = glm::rotate(model, mRotateAngles.x, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, mRotateAngles.y, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, mRotateAngles.z, glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(mUniModel(), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(mUniView(), 1, GL_FALSE, glm::value_ptr(scene->camera().matrix()));
}
