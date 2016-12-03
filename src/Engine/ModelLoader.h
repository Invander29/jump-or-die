#pragma once
#include <vector>
#include <glm/glm.hpp>

class ModelLoader
{
public:
	bool load(const std::string& filename);

	const std::vector<glm::vec3>& vertices() const { return mVertices; }
	const std::vector<glm::vec2>& uv() const { return mUVS; }
	const std::vector<glm::vec3>& normals() const { return mNormals; }

private:
	std::vector <glm::vec3> mVertices;
	std::vector <glm::vec2> mUVS;
	std::vector <glm::vec3> mNormals;
};
