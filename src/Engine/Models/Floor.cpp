//
// Created by invander on 24.10.16.
//

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Floor.h"

using namespace Models;

Floor::Floor(std::shared_ptr<Managers::ShaderManager::Program> program, float width, float length, float height)
		: ModelObject(program, false), mWidth(width), mLength(length), mHeight(height)
{
	// Prepare buffer of vertices
	const GLfloat vertices[] = {
			-1.0f * width,	height,	1.0f * length,
			1.0f * width,	height,	1.0f * length,
			1.0f * width,	height,	-1.0f * length,
			-1.0f * width,	height,	-1.0f * length,
	};

	// Prepare buffer of normals
	const GLfloat normals[] = {
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0
	};

	// 1. Bind Vertex Array Object
	glBindVertexArray(mVAO);

	// 2. Copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 3. Then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// 2. Copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, mNBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);

	// 3. Then set the vertex attributes pointers
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(1);

	//4. Unbind the VBO, VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Floor::~Floor()
{
}

void Floor::draw(Scenes::Scene* scene)
{
	ModelObject::draw(scene);
}

void Floor::update() {

}
