#pragma once

#include <glm/glm.hpp>

namespace Scenes
{
	class Scene;
}

namespace Lighting {

	/**
	 * Simple class for lighting a scene
	 */
	class Light
	{
	public:
		/**
		 * Create light on default positions
		 */
		explicit Light() {}

		/**
		 * Create light on position with color
		 */
		explicit Light(const glm::vec3& position, const glm::vec3& color)
			: mPosition(position), mColor(color)
		{
		}

		/**
		 * Get light position
		 */
		glm::vec3& position() { return mPosition; }
		const glm::vec3& position() const { return mPosition; }

		/**
		 * Get light color
		 */
		glm::vec3& color() { return mColor; }
		const glm::vec3& color() const { return mColor; }

		/**
		 * Set light position
		 */
		void setPosition(float x, float y, float z) { setPosition(glm::vec3(x, y, z)); }
		void setPosition(const glm::vec3& position) { mPosition = position; }

		/**
		 * Set light color
		 */
		void setColor(float r, float g, float b) { setColor(glm::vec3(r, g, b)); }
		void setColor(const glm::vec3& color) { mColor = color; }

	private:
		glm::vec3 mPosition = glm::vec3(0, 0, 0);
		glm::vec3 mColor = glm::vec3(1, 1, 1);
	};

}
