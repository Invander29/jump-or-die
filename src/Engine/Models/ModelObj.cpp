#include "ModelObj.h"
#include "../Utils/ModelLoader.h"
#include "../Application.h"
#include "../Utils/Message.h"

Models::ModelObj::ModelObj(std::shared_ptr<Managers::ShaderManager::Program> program, const std::string& obj, const std::string& texture)
	: ModelObject(program, false, false, false, false)
{
	bindUniform(mProgram, mUniTexture, "texture");
	std::string textureName = texture + ".png";

	// Load texture
	mTexture = Application::instance().resourceManager().texture(textureName);

	// Load model
	mModel = Application::instance().resourceManager().model(obj);
}

Models::ModelObj::~ModelObj()
{
	if (mTexture) {
		Application::instance().resourceManager().deleteTexture(mTexture->name());
	}
}

void Models::ModelObj::draw(Scenes::Scene* scene)
{
	ModelObject::draw(scene);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTexture->id());
	glUniform1i(mUniTexture(), 0);

	glBindVertexArray(mModel->vao());
	glDrawArrays(GL_TRIANGLES, 0, mModel->size());
	glBindVertexArray(0);
}
