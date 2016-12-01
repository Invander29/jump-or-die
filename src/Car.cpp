﻿#include "Car.h"
#include "Engine/Application.h"

const float Car::AREA_X = 25;

Car::Car(GLuint program, bool fromRight, float delayTime, float waitTime, float speed)
	: CubeColor(program, 0.8f, 1.0f, 0.0f, 0.0f), mFromRight(fromRight), 
		mTime(-delayTime), mWaitTime(waitTime), mSpeed(speed)
{
	// Create on one side or other
	mVisible = false;
}

void Car::update()
{
	// Wait for a while, after that show yourself
	if (!mVisible) {
		mTime += Application::instance().speed();
		if (mTime > mWaitTime) {
			mTime = 0;
			mVisible = true;
		}
	} 
	// Move to next side
	else {
		// Rigth to left
		if (mFromRight) {
			mPosition.x -= mSpeed * Application::instance().speed();
			if (mPosition.x < -AREA_X) {
				mPosition.x = ((mFromRight) ? 1 : -1) * AREA_X;
			}
		} 
		// Left to right
		else {
			mPosition.x += mSpeed * Application::instance().speed();
			if (mPosition.x > AREA_X) {
				mPosition.x = ((mFromRight) ? 1 : -1) * AREA_X;
			}
		}
	}
}

void Car::draw(const glm::mat4& view)
{
	if (!mVisible) {
		return;
	}

	CubeColor::draw(view);
}
