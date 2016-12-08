#include "ModelLoader.h"
#include "Message.h"

#include <tiny_obj_loader.h>
#include <fstream>

using namespace Utils;

bool ModelLoader::load(const std::string& filename)
{
	std::string fullname = "models/" + filename;

	using namespace tinyobj;
	using namespace Utils;

	attrib_t attrib;
	std::vector<shape_t> shapes;
	std::vector<material_t> materials;
	std::string error;

	bool ret = LoadObj(&attrib, &shapes, &materials, &error, fullname.c_str(), "models/");
	if (!ret) {
		Message::error(__FILE__, __LINE__, "Cannot load obj file %s", error.c_str());
		return false;
	}

	// Convert to VBO
	mVertices.clear();
	int count = shapes[0].mesh.indices.size() / 3;
	mVertices.reserve(count);

	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {
			Vertex v;

			v.position = {
				attrib.vertices[3 * index.vertex_index + 0],
				attrib.vertices[3 * index.vertex_index + 1],
				attrib.vertices[3 * index.vertex_index + 2]
			};

			v.normal = {
				attrib.normals[3 * index.normal_index + 0],
				attrib.normals[3 * index.normal_index + 1],
				attrib.normals[3 * index.normal_index + 2]
			};

			v.texcoord = {
				attrib.texcoords[2 * index.texcoord_index + 0],
				attrib.texcoords[2 * index.texcoord_index + 1]
			};

			mVertices.push_back(v);
		}
	}

	return true;
}

bool ModelLoader::load(float* data, size_t size)
{
	mVertices.clear();
	mVertices.reserve(size / 8);

	for (size_t i = 0; i < size - 7; i += 8) {
		Vertex v;

		v.position.x = data[i + 0];
		v.position.y = data[i + 1];
		v.position.z = data[i + 2];

		v.normal.x = data[i + 3];
		v.normal.y = data[i + 4];
		v.normal.z = data[i + 5];

		v.texcoord.x = data[i + 6];
		v.texcoord.y = data[i + 7];

		mVertices.push_back(v);
	}

	return true;
}

bool ModelLoader::load(double* data, size_t size)
{
	mVertices.clear();
	mVertices.reserve(size);

	for (size_t i = 0; i < size; ++i) {
		Vertex v;
		size_t index = i * 8;

		v.position.x = static_cast<float>(data[index + 0]);
		v.position.y = static_cast<float>(data[index + 1]);
		v.position.z = static_cast<float>(data[index + 2]);

		v.normal.x = static_cast<float>(data[index + 3]);
		v.normal.y = static_cast<float>(data[index + 4]);
		v.normal.z = static_cast<float>(data[index + 5]);

		v.texcoord.x = static_cast<float>(data[index + 6]);
		v.texcoord.y = static_cast<float>(data[index + 7]);

		mVertices.push_back(v);
	}

	return true;
}

bool ModelLoader::save(const std::string& filename)
{
	std::ofstream file(filename);
	if (!file.is_open()) {
		return false;
	}

	file << "size_t ModelSize = " << mVertices.size() << ";" << std::endl;

	file << "double Model[] = {" << std::endl;

	for (auto vertex : mVertices) {
		file << vertex.position.x << ", ";
		file << vertex.position.y << ", ";
		file << vertex.position.z << ", ";

		file << vertex.normal.x << ", ";
		file << vertex.normal.y << ", ";
		file << vertex.normal.z << ", ";

		file << vertex.texcoord.x << ", ";
		file << vertex.texcoord.y << ", ";
		
		file << std::endl;
	}

	file << "};" << std::endl;
	return true;
}
