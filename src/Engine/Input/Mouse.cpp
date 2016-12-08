//
// Created by invander on 24.10.16.
//

#include "Mouse.h"
#include <cstring>

using namespace Input;

Mouse::Mouse() 
{
	memset(mDown, 0, sizeof(mDown));
	memset(mChange, 0, sizeof(mChange));
}

Mouse::~Mouse() 
{
}

void Mouse::onButtonDown(int button)
{
	if (button < 0 || button >= BUTTON_COUNT) {
		return;
	}
	mDown[button] = true;
}

void Mouse::onButtonUp(int button)
{
	if (button < 0 || button >= BUTTON_COUNT) {
		return;
	}
	mDown[button] = false;
}

void Mouse::onMove(double x, double y)
{
	mLastPosition = mPosition;
	mPosition.x = static_cast<float>(x);
	mPosition.y = static_cast<float>(y);
}

void Mouse::onNextFrame()
{
	memset(mChange, 0, sizeof(mChange));
}

bool Mouse::isButtonTrigered(int button) const 
{
	if (button < 0 || button >= BUTTON_COUNT) {
		return false;
	}
	return mChange[button];
}

bool Mouse::isButtonPressed(int button) const 
{
	if (button < 0 || button >= BUTTON_COUNT) {
		return false;
	}
	return mDown[button];
}

bool Mouse::isButtonReleased(int button) const 
{
	if (button < 0 || button >= BUTTON_COUNT) {
		return false;
	}
	return !mDown[button];
}
