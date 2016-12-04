#pragma once
#include "Engine/Models/ModelObj.h"

class TextGameOver : public Models::ModelObj
{
public:
	explicit TextGameOver(const std::shared_ptr<Managers::ShaderManager::Program>& program)
		: ModelObj(program, "gameover", "gameover")
	{
		mScale = glm::vec3(1.0f);
	}
};

MAKE_SMART(TextGameOver);
