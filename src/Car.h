#pragma once

#include "Engine/Models/CubeColor.h"

class Car : public Models::CubeColor
{
public:
	explicit Car(GLuint program, bool fromRight, float delayTime, float waitTime, float mSpeed);

	void update() override;
	void draw(const glm::mat4& view) override;

protected:
	static const float AREA_X;

	bool mFromRight;
	bool mVisible;

	float mTime;
	float mWaitTime;
	float mSpeed;
};

MAKE_SMART(Car);