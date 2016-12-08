#include "Model.h"
#include "../Utils/Message.h"
#include "../Application.h"
#include "../Utils/ModelLoader.h"

Graphics::Model::~Model()
{
	if (mVAO != 0) {
		glDeleteBuffers(1, &mVAO);
	}

	if (mVBO != 0) {
		glDeleteBuffers(1, &mVBO);
	}
}

extern double ModelCar[];
extern size_t ModelCarSize;
extern double ModelGameOver[];
extern size_t ModelGameOverSize;
extern double ModelMch[];
extern size_t ModelMchSize;
extern double ModelPress[];
extern size_t ModelPressSize;
extern double ModelStart[];
extern size_t ModelStartSize;
extern double ModelTree[];
extern size_t ModelTreeSize;

bool Graphics::Model::load(const std::string& file)
{
	Utils::ModelLoader loader;

	// Load from memory
	if (file[0] == ':') {
		double *data;
		size_t size;

		if (file.compare(":Car") == 0) {
			data = ModelCar;
			size = ModelCarSize;
		}
		else if (file.compare(":GameOver") == 0) {
			data = ModelGameOver;
			size = ModelGameOverSize;
		}
		else if (file.compare(":Mch") == 0) {
			data = ModelMch;
			size = ModelMchSize;
		}
		else if (file.compare(":Press") == 0) {
			data = ModelPress;
			size = ModelPressSize;
		}
		else if (file.compare(":Start") == 0) {
			data = ModelStart;
			size = ModelStartSize;
		}
		else if (file.compare(":Tree") == 0) {
			data = ModelTree;
			size = ModelTreeSize;
		}
		else {
			return false;
		}

		if (!loader.load(data, size)) {
			Utils::Message::error(__FILE__, __LINE__, "Cannot load data %s", file.c_str());
			return false;
		}
	}
	// Load from file
	else {
		if (!loader.load(file)) {
			Utils::Message::error(__FILE__, __LINE__, "Cannot load file %s", file.c_str());
			return false;
		}
	}

	// Generate buffers
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);

	// Load to GPU
	// 1. Bind Vertex Array Object
	glBindVertexArray(mVAO);

	// 2. Copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	mNumOfVertices = loader.vertices().size();
	glBufferData(GL_ARRAY_BUFFER, mNumOfVertices * sizeof(Utils::Vertex), loader.vertices().data(), GL_STATIC_DRAW);

	// 3. Then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Utils::Vertex), (GLvoid*)offsetof(Utils::Vertex, position));
	glEnableVertexAttribArray(0);

	// 3. Then set the normals attributes pointers
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Utils::Vertex), (GLvoid*)offsetof(Utils::Vertex, normal));
	glEnableVertexAttribArray(1);

	// 3. Then set the texture coord attributes pointers
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Utils::Vertex), (GLvoid*)offsetof(Utils::Vertex, texcoord));
	glEnableVertexAttribArray(2);

	//4. Unbind the VBO, VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return true;
}


