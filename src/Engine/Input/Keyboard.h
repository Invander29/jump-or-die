//
// Created by invander on 24.10.16.
//

#pragma once

#include <SDL2/SDL.h>

namespace Input {

	/**
	 * Class for handling keyboard events
	 */
	class Keyboard {
	public:
		explicit Keyboard();
		~Keyboard();

		/**
		 * Restore init values
		 * @return true if success
		 */
		bool init();

		/**
		 * Update state of keyboard
		 */
		void update();

		/**
		 * Check if key was clicked
		 * @param keyCode Scancode of key
		 * @return true if key was clicked
		 */
		bool isKeyTriggered(const SDL_Scancode keyCode) const;

		/**
		 * Check if key is pressed
		 * @param keyCode Scancode of key
		 * @return true if key is pressed
		 */
		bool isKeyPressed(const SDL_Scancode keyCode) const;

		/**
		 * Check if key was released
		 * @param keyCode Scancode of key
		 * @return true if key was released
		 */
		bool isKeyReleased(const SDL_Scancode keyCode) const;

	private:
		Uint8 mPrevInput[SDL_NUM_SCANCODES];
		Uint8 mCurrentInput[SDL_NUM_SCANCODES];
	};
}
