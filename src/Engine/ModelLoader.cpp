#include "ModelLoader.h"
#include "Utils/Message.h"
#include <fstream>
#include <string>
#include <sstream>

using namespace Utils;

bool ModelLoader::load(const std::string& filename)
{
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> tmpVertices; 
	std::vector<glm::vec2> tmpUvs;
	std::vector<glm::vec3> tmpNormals;

	std::ifstream file("models/" + filename);
	if (!file.is_open()) {
		return Message::error(__FILE__, __LINE__, "Cannot open file for read %s", filename.c_str());
	}

	while (!file.eof()) {
		std::string line;
		std::getline(file, line);

		std::string word;
		file >> word;

		// Vertex
		if (word.compare("v") == 0) {
			glm::vec3 vertex;
			for (int i = 0; i < 3; ++i) {
				file >> word;
				vertex[i] = std::strtof(word.c_str(), nullptr);
			}
			tmpVertices.push_back(vertex);
		}
		// Texture
		else if (word.compare("vt") == 0) {
			glm::vec2 uv;
			for (int i=0; i<2; ++i) {
				file >> word;
				uv[i] = std::strtof(word.c_str(), nullptr);
			}
			tmpUvs.push_back(uv);
		}
		// Normal
		else if (word.compare("vn") == 0) {
			glm::vec3 normal;
			for (int i=0; i<3; ++i) {
				file >> word;
				normal[i] = std::strtof(word.c_str(), nullptr);
			}
			tmpNormals.push_back(normal);
		}
		// F
		else if (word.compare("f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			
			for (int i = 0; i < 3; ++i) {
				std::stringstream ss;
				file >> word;
				ss.str(word);
				int index = 0;
				while (std::getline(ss, word, '/')) {
					unsigned int tmp = std::strtoul(word.c_str(), nullptr, 10);
					switch (index) {
					case 0: vertexIndex[i] = tmp; break;
					case 1: uvIndex[i] = tmp; break;
					case 2: normalIndex[i] = tmp; break;
					default:
						Message::error(__FILE__, __LINE__, "This should never happen!");
					}
					++index;
				}
			}

			for (int i = 0; i < 3; ++i) {
				vertexIndices.push_back(vertexIndex[i]);
				uvIndices.push_back(uvIndex[i]);
				normalIndices.push_back(normalIndex[i]);
			}
		}
	}

	for (unsigned int i = 0U; i < vertexIndices.size(); ++i) {
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = tmpVertices[vertexIndex - 1];
		mVertices.push_back(vertex);
	}

	for (unsigned int i = 0U; i < uvIndices.size(); ++i) {
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 uv = tmpUvs[uvIndex - 1];
		mUVS.push_back(uv);
	}

	for (unsigned int i = 0U; i < normalIndices.size(); ++i) {
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = tmpNormals[normalIndex - 1];
		mNormals.push_back(normal);
	}

	return true;
}

