//
// Created by invander on 24.10.16.
//

#include "Mouse.h"

using namespace Input;

Mouse::Mouse() {
	init();
}

Mouse::~Mouse() {

}

bool Mouse::init() {
	mPrevX = 0;
	mPrevY = 0;
	mCurrentState = 0;

	mCurrentState = SDL_GetMouseState(&mCurrentX, &mCurrentY);

	mWheelX = 0;
	mWheelY = 0;
	return true;
}

void Mouse::update() {
	mPrevX = mCurrentX;
	mPrevY = mCurrentY;
	mPrevState = mCurrentState;

	mCurrentState = SDL_GetMouseState(&mCurrentX, &mCurrentY);

	mWheelX = 0;
	mWheelY = 0;
}

void Mouse::receiveEvent(const SDL_Event &event) {
	switch (event.type) {
		case SDL_MOUSEWHEEL:
			mWheelX = event.wheel.x;
			mWheelY = event.wheel.y;
			break;

		default:
			break;
	}
}

const glm::vec2 Mouse::getPosition() const {
	return glm::vec2(mCurrentX, mCurrentY);
}

const glm::vec2 Mouse::getMove() const {
	return glm::vec2(mCurrentX - mPrevX, mCurrentY - mPrevY);
}

bool Mouse::isButtonTrigered(const Uint32 button) const {
	return ((SDL_BUTTON(button) & mCurrentState) != 0) && ((SDL_BUTTON(button) & mPrevState) == 0);
}

bool Mouse::isButtonPressed(const Uint32 button) const {
	return (SDL_BUTTON(button) & mCurrentState) != 0;
}

bool Mouse::isButtonReleased(const Uint32 button) const {
	return ((SDL_BUTTON(button) & mCurrentState) == 0) && ((SDL_BUTTON(button) & mPrevState) != 0);
}

int Mouse::getWheelX() const {
	return mWheelX;
}

int Mouse::getWheelY() const {
	return mWheelY;
}
