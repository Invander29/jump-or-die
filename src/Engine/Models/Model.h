//
// Created by invander on 22.10.16.
//

#pragma once


#include "GameObject.h"

namespace Models {

	/**
	 * Simple abstract model for game scene
	 */
	class Model : public GameObject {
	public:
		/**
		 * Create new model
		 * @param program program ID for OpenGL
		 */
		explicit Model(GLuint program, bool createEBO = true, bool createVBO = true, bool createVAO = true);
		virtual ~Model() = 0;

		/**
		 * Get position
		 * @return position
		 */
		glm::vec3 position() const { return mPosition; }

		/**
		 * Get X
		 * @return x
		 */
		float x() const { return mPosition.x; }

		/**
		 * Get y
		 * @return y
		 */
		float y() const { return mPosition.y; }

		/**
		 * Get z
		 * @return z
		 */
		float z() const { return mPosition.z; }

		/**
		 * Set position
		 * @param position new position
		 */
		void setPosition(const glm::vec3& position) { mPosition = position; }

		/**
		 * Set position
		 * @param x new x
		 * @param y new y
		 * @param z new z
		 */
		void setPosition(float x, float y, float z) { setX(x); setY(y); setZ(z); }

		/**
		 * Set x
		 * @param x new x
		 */
		void setX(float x) { mPosition.x = x; }

		/**
		 * Set y
		 * @param y new y
		 */
		void setY(float y) { mPosition.y = y; }

		/**
		 * Set z
		 * @param z new z
		 */
		void setZ(float z) { mPosition.z = z; }

		/**
		 * Move
		 * @param move append to current position
		 */
		void move(const glm::vec3& move) { mPosition += move; }

		/**
		 * Move
		 * @param x append to x
		 * @param y append to y
		 * @param z append yo z
		 */
		void move(float x, float y, float z) { moveX(x); moveY(y); moveZ(z); }

		/**
		 * Move
		 * @param x append to x
		 */
		void moveX(float x) { mPosition.x += x; }

		/**
		 * Move
		 * @param y append to y
		 */
		void moveY(float y) { mPosition.y += y; }

		/**
		 * Move
		 * @param z append to z
		 */
		void moveZ(float z) { mPosition.z += z; }

		void update() override;
		void draw(const glm::mat4& view) override;

	protected:
		GLuint mProgram = 0;
		GLuint mVAO = 0;
		GLuint mVBO = 0;
		GLuint mEBO = 0;
		GLint mMvp = -1;
		glm::vec3 mPosition;
	};

}