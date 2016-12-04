#pragma once

#include <glm/glm.hpp>

namespace Scenes
{
	class Scene;
}

namespace Lighting {

	class Light
	{
	public:
		explicit Light() {}
		explicit Light(const glm::vec3& position, const glm::vec3& color)
			: mPosition(position), mColor(color)
		{
		}

		glm::vec3& position() { return mPosition; }
		const glm::vec3& position() const { return mPosition; }

		glm::vec3& color() { return mColor; }
		const glm::vec3& color() const { return mColor; }

		void setPosition(float x, float y, float z) { setPosition(glm::vec3(x, y, z)); }
		void setPosition(const glm::vec3& position) { mPosition = position; }

		void setColor(float r, float g, float b) { setColor(glm::vec3(r, g, b)); }
		void setColor(const glm::vec3& color) { mColor = color; }

	private:
		glm::vec3 mPosition = glm::vec3(0, 0, 0);
		glm::vec3 mColor = glm::vec3(1, 1, 1);
	};

}
