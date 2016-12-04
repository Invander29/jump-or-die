#include "ModelLoader.h"
#include "Message.h"
#include <tiny_obj_loader.h>

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

