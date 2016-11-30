//
// Created by invander on 24.10.16.
//

#include "Keyboard.h"
#include <cstring>

using namespace Input;

Keyboard::Keyboard() {
	memset(mDown, 0, sizeof(mDown));
	memset(mChange, 0, sizeof(mChange));
}

Keyboard::~Keyboard() {

}

void Keyboard::onNextFrame()
{
	memset(mChange, 0, sizeof(mChange));
}


void Keyboard::onKeyDown(int key, int scancode)
{
	if (key < 0 || key >= KEY_COUNT) {
		return;
	}

	mDown[key] = true;
	mChange[key] = true;
}

void Keyboard::onKeyUp(int key, int scancode)
{
	if (key < 0 || key >= KEY_COUNT) {
		return;
	}

	mDown[key] = false;
}

bool Keyboard::isKeyTriggered(int key) const
{
	if (key < 0 || key >= KEY_COUNT) {
		return false;
	}

	return mChange[key];
}

bool Keyboard::isKeyPressed(int key) const 
{
	if (key < 0 || key >= KEY_COUNT) {
		return false;
	}

	return mDown[key];
}

bool Keyboard::isKeyReleased(int key) const 
{
	if (key < 0 || key >= KEY_COUNT) {
		return false;
	}

	return !mDown[key];
}
