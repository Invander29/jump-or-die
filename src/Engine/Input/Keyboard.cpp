//
// Created by invander on 24.10.16.
//

#include <SDL2/SDL.h>
#include "Keyboard.h"
#include <cstring>

using namespace Input;

Keyboard::Keyboard() {
	init();
}

Keyboard::~Keyboard() {

}

bool Keyboard::init() {
	memset(mPrevInput, 0, sizeof(Uint8) * SDL_NUM_SCANCODES);
	memcpy(mCurrentInput, SDL_GetKeyboardState(nullptr), sizeof(Uint8) * SDL_NUM_SCANCODES);
	return true;
}

void Keyboard::update() {
	memcpy(mPrevInput, mCurrentInput, sizeof(Uint8) * SDL_NUM_SCANCODES);
	memcpy(mCurrentInput, SDL_GetKeyboardState(nullptr), sizeof(Uint8) * SDL_NUM_SCANCODES);
}

bool Keyboard::isKeyTriggered(const SDL_Scancode keyCode) const {
	return mCurrentInput[keyCode] == 1 && mPrevInput[keyCode] == 0;
}

bool Keyboard::isKeyPressed(const SDL_Scancode keyCode) const {
	return mCurrentInput[keyCode] == 1;
}

bool Keyboard::isKeyReleased(const SDL_Scancode keyCode) const {
	return mCurrentInput[keyCode] == 0 && mPrevInput[keyCode] == 1;
}
