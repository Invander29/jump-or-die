#include "TextPressSpace.h"
#include "Engine/Application.h"
#include "Images/Images.h"

TextPressSpace::TextPressSpace(const std::shared_ptr<Managers::ShaderManager::Program>& program)
	: ModelObj(program, ":Press", 0.8f, 0.0f, 0.0f)
{
	mScale = glm::vec3(1.0f);
	mRotateAngles.x = -0.5f;
	mVisible = true;
}

void TextPressSpace::draw(Scenes::Scene* scene)
{
	if (!mVisible) {
		return;
	}

	ModelObj::draw(scene);
}
