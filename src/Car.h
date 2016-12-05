#pragma once

#include "Engine/Models/ModelObj.h"

class Car : public Models::ModelObj
{
public:
	explicit Car(std::shared_ptr<Managers::ShaderManager::Program> program, bool fromRight, float delayTime, float waitTime, float mSpeed);

	void update() override;
	void draw(Scenes::Scene* scene) override;
	void gameover();

protected:
	static const float AREA_X;

	bool mFromRight;
	bool mVisible;
	bool stopped;

	float mTime;
	float mWaitTime;
	float mSpeed;
};

MAKE_SMART(Car);