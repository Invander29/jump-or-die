#include "TextStart.h"
#include "Engine/Application.h"
#include "Images/Images.h"

TextStart::TextStart(const std::shared_ptr<Managers::ShaderManager::Program>& program)
	: ModelObj(program, ":Start", 0.0f, 0.5f, 0.5f)
{
	mScale = glm::vec3(1.0f);
	mRotateAngles.x = -0.5f;
	mVisible = true;
}

void TextStart::draw(Scenes::Scene* scene)
{
	if (!mVisible) {
		return;
	}

	ModelObj::draw(scene);
}
