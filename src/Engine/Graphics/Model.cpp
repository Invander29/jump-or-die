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

bool Graphics::Model::load(const std::string& file)
{
	// Load from file
	Utils::ModelLoader loader;
	if (!loader.load(file)) {
		Utils::Message::error(__FILE__, __LINE__, "Cannot load file %s", file.c_str());
		return false;
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


