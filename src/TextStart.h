#pragma once
#include "Engine/Models/ModelObj.h"

class TextStart : public Models::ModelObj
{
public:

	explicit TextStart(const std::shared_ptr<Managers::ShaderManager::Program>& program)
		: ModelObj(program, "start", "start")
	{
		mScale = glm::vec3(1.0f);
	}
};

MAKE_SMART(TextStart);