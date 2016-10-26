//
// Created by invander on 24.10.16.
//

#pragma once

#include <SDL2/SDL.h>
#include <glm/vec2.hpp>

namespace Input {

	/**
	 * Class for handling mouse events
	 */
	class Mouse {
	public:
		explicit Mouse();
		~Mouse();

		/**
		 * Init values
		 * @return true if success
		 */
		bool init();

		/**
		 * Update state of mouse
		 */
		void update();

		/**
		 * Process events
		 * @param event event from SDL
		 */
		void receiveEvent(const SDL_Event& event);

		/**
		 * Get mouse X, Y position
		 * @return position of mouse
		 */
		const glm::vec2 getPosition() const;

		/**
		 * Get mouse move
		 * @return difference of previous position and current
		 */
		const glm::vec2 getMove() const;

		/**
		 * Check if mouse button was triggered
		 * @param button code of button
		 * @return true if mouse button was triggered
		 */
		bool isButtonTrigered(const Uint32 button) const;

		/**
		 * Check if mouse button is pressed
		 * @param button code of button
		 * @return true if mouse button is pressed
		 */
		bool isButtonPressed(const Uint32 button) const;

		/**
		 * Check if mouse button was released
		 * @param button code of button
		 * @return true if mouse button was released
		 */
		bool isButtonReleased(const Uint32 button) const;

		/**
		 * Check for wheel move
		 * @return diff of mouse wheel
		 */
		int getWheelX() const;

		/**
		 * Check for wheel move
		 * @return diff of mouse wheel
		 */
		int getWheelY() const;

	private:
		int mCurrentX;
		int mCurrentY;
		Uint32 mCurrentState;

		int mPrevX;
		int mPrevY;
		Uint32 mPrevState;

		Sint32 mWheelX;
		Sint32 mWheelY;
	};

}