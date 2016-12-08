//
// Created by invander on 24.10.16.
//

#pragma once

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

namespace Input {

	/**
	 * Class for handling keyboard events
	 */
	class Keyboard {
	public:
		explicit Keyboard();
		~Keyboard();

		/**
		 * Listeners connected to GLFW callback events
		 */
		void onKeyDown(int key, int scancode);
		void onKeyUp(int key, int scancode);
		void onNextFrame();

		/**
		 * Check if key was clicked
		 * @param key code of key
		 * @return true if key was clicked
		 */
		bool isKeyTriggered(int key) const;

		/**
		 * Check if key is pressed
		 * @param key code of key
		 * @return true if key is pressed
		 */
		bool isKeyPressed(int key) const;

		/**
		 * Check if key was released
		 * @param key code of key
		 * @return true if key was released
		 */
		bool isKeyReleased(int key) const;

	private:
		static const int KEY_COUNT = 512;
		bool mDown[KEY_COUNT];
		bool mChange[KEY_COUNT];
	};
}
