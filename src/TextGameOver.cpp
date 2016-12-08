#include "TextGameOver.h"
#include "Engine/Application.h"
#include "Images/Images.h"

TextGameOver::TextGameOver(const std::shared_ptr<Managers::ShaderManager::Program>& program)
	: ModelObj(program, ":GameOver", 0.8f, 0.0f, 0.0f)
{
	//zmena velkosti
	mScale = glm::vec3(1.0f);
	//rotacia objektu
	mRotateAngles.x = -0.5f;
	//implicitne je objekt viditelny
	mVisible = true;
}

void TextGameOver::draw(Scenes::Scene* scene)
{
	//ak nie je viditelny nerobime nic
	if (!mVisible) {
		return;
	}

	ModelObj::draw(scene);
}
