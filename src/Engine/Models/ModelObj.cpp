#include "ModelObj.h"
#include "../Utils/ModelLoader.h"
#include "../Application.h"
#include <glm/gtc/type_ptr.hpp>

Models::ModelObj::ModelObj(std::shared_ptr<Managers::ShaderManager::Program> program, const std::string& obj, Image* image)
	: ModelObject(program, false, false, false, false)
{
	bindUniform(mProgram, mUniTexture, "texture");

	// Load texture
	mTexture = Application::instance().resourceManager().texture(image->name, image);

	// Load model
	mModel = Application::instance().resourceManager().model(obj);
}

Models::ModelObj::ModelObj(std::shared_ptr<Managers::ShaderManager::Program> program, const std::string& obj, float r, float g, float b)
	: ModelObject(program, false, false, false, false)
{
	bindUniform(mProgram, mUniColor, "color");

	// Save color
	mColor = glm::vec3(r, g, b);

	// Load model
	mModel = Application::instance().resourceManager().model(obj);
}

Models::ModelObj::~ModelObj()
{
}

void Models::ModelObj::draw(Scenes::Scene* scene)
{
	ModelObject::draw(scene);

	if (mTexture) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mTexture->id());
		glUniform1i(mUniTexture(), 0);
	}
	else{
		glUniform3fv(mUniColor(), 1, glm::value_ptr(mColor));
	}

	glBindVertexArray(mModel->vao());
	glDrawArrays(GL_TRIANGLES, 0, mModel->size());
	glBindVertexArray(0);
}
