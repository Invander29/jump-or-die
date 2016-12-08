//
// Created by invander on 24.10.16.
//

#pragma once

#include <glm/vec2.hpp>
#include <cstdint>

namespace Input {

	/**
	 * Class for handling mouse events
	 */
	class Mouse {
	public:
		explicit Mouse();
		~Mouse();

		/**
		 * Listeners connected to GLFW callback events
		 */
		void onButtonDown(int button);
		void onButtonUp(int button);
		void onMove(double x, double y);
		void onNextFrame();

		/**
		 * Get mouse X, Y position
		 * @return position of mouse
		 */
		glm::vec2 position() const { return mPosition; }

		/**
		 * Get mouse move
		 * @return difference of previous position and current
		 */
		glm::vec2 lastMove() const { return mPosition - mLastPosition; }

		/**
		 * Check if mouse button was triggered
		 * @param button code of button
		 * @return true if mouse button was triggered
		 */
		bool isButtonTrigered(int button) const;

		/**
		 * Check if mouse button is pressed
		 * @param button code of button
		 * @return true if mouse button is pressed
		 */
		bool isButtonPressed(int button) const;

		/**
		 * Check if mouse button was released
		 * @param button code of button
		 * @return true if mouse button was released
		 */
		bool isButtonReleased(int button) const;

	private:
		glm::vec2 mPosition;
		glm::vec2 mLastPosition;

		static const int BUTTON_COUNT = 10;
		bool mDown[BUTTON_COUNT];
		bool mChange[BUTTON_COUNT];
	};

}