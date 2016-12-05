//
// Created by invander on 22.10.16.
//

#pragma once


#include "GameObject.h"
#include "../Managers/ShaderManager.h"

namespace Models {

	/**
	 * Simple abstract model for game scene
	 */
	class ModelObject : public GameObject {
	public:
		/**
		 * Create new model
		 * @param program program ID for OpenGL
		 */
		explicit ModelObject(std::shared_ptr<Managers::ShaderManager::Program> program, bool createEBO = true, bool createVBO = true, bool createVAO = true, bool createNBO = true);
		virtual ~ModelObject() = 0;

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
		void draw(Scenes::Scene* scene) override;

	protected:
		std::shared_ptr<Managers::ShaderManager::Program> mProgram;

		GLuint mVAO = 0;
		GLuint mVBO = 0;
		GLuint mNBO = 0;
		GLuint mEBO = 0;

		Uniform mUniView;
		Uniform mUniModel;
		Uniform mUniLightPos;
		Uniform mUniLightColor;
		Uniform mUniViewPosition;

		glm::vec3 mPosition = glm::vec3(0);
		glm::vec3 mScale = glm::vec3(1);
		glm::vec3 mRotateAngles = glm::vec3(0);
	};

}
