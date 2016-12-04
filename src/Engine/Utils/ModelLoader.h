#pragma once

#include <GL/gl3w.h>
#include <vector>
#include <glm/glm.hpp>

namespace Utils {

	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texcoord;
	};

	class ModelLoader
	{
	public:
		bool load(const std::string& filename);
		const std::vector<Vertex>& vertices() const { return mVertices; }

	private:
		std::vector <Vertex> mVertices;
		std::vector <GLuint> mIndices;
	};

}