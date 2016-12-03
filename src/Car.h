#pragma once

#include "Engine/Models/CubeColor.h"

class Car : public Models::CubeColor
{
public:
	explicit Car(std::shared_ptr<Managers::ShaderManager::Program> program, bool fromRight, float delayTime, float waitTime, float mSpeed);

	void update() override;
	void draw(Scenes::Scene* scene) override;

protected:
	static const float AREA_X;

	bool mFromRight;
	bool mVisible;

	float mTime;
	float mWaitTime;
	float mSpeed;
};

MAKE_SMART(Car);