//
// Created by invander on 25.10.16.
//

#pragma once

#include <glm/glm.hpp>

namespace Scenes {

	/**
	 * Class for easier manpulation with camera
	 */
	class Camera {
	public:
		/**
		 * Create camera object
		 * @param fov Field of view
		 * @param near Near plane
		 * @param far Far plane
		 */
		explicit Camera(float fov, float near, float far);

		/**
		 * Look from place to place
		 * @param position Position of camera
		 * @param lookAt Position of the center of view
		 */
		void lookAt(glm::vec3 position, glm::vec3 lookAt);

		/**
		 * Move camera to specific position
		 * @param vector Vector of move
		 */
		void move(glm::vec3 vector);

		/**
		 * Move camera to right
		 * @param x movement
		 */
		void moveRight(float x);

		/**
		 * Move camera up
		 * @param y movement
		 */
		void moveUp(float y);

		/**
		 * Move camera to forward
		 * @param z movement
		 */
		void moveForward(float z);

		/**
		 * Rotate camera around vector with specific angle
		 * @param angle Angle of rotation
		 * @param vector Vector of rotation
		 */
		void rotate(float angle, glm::vec3 vector);

		/**
		 * Rotate camera right
		 * @param angle rotation
		 */
		void lookRight(float angle);

		/**
		 * Rotate camera up
		 * @param angle rotation
		 */
		void lookUp(float angle);

		/**
		 * Rotate camera down
		 * @param angle rotation
		 */
		void lookSide(float angle);

		/**
		 * Get current matrix
		 * @return precomputed matrix
		 */
		glm::mat4 matrix() const { return mMatrix; }

	private:
		glm::mat4 mPerspective;
		glm::mat4 mMatrix;
		glm::mat4 mView = glm::mat4(1.0f);
	};

}