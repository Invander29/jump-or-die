﻿#pragma once
#include "Engine/Models/ModelObj.h"

class TextStart : public Models::ModelObj
{
public:

	explicit TextStart(const std::shared_ptr<Managers::ShaderManager::Program>& program)
		: ModelObj(program, "start", "start")
	{
		mScale = glm::vec3(1.0f);
		mRotateAngles.x = -0.5f;
		mVisible = true;
	}

	void draw(Scenes::Scene* scene) override;
	void setVisibility(bool value) { mVisible = value; }
	bool getVisibility() { return mVisible; }


private:
	bool mVisible;
};

MAKE_SMART(TextStart);