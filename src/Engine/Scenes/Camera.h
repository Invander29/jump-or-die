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

		void setPosition(float x, float y, float z) { setPosition(glm::vec3(x, y, z)); }
		void setPosition(const glm::vec3& position) { mPosition = position; }

		/**
		 * Move camera to specific position
		 * @param vector Vector of move
		 */
		void move(const glm::vec3& vector);

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

		const glm::vec3& position() const { return mPosition; }

	private:
		void updateVectors();

		glm::mat4 mPerspective;
		glm::mat4 mMatrix;

		glm::vec3 mPosition;
		glm::vec3 mFront;
		glm::vec3 mUp;
		glm::vec3 mRight;
		glm::vec3 mWorldUp;

		float mYaw;
		float mPitch;
	};

}