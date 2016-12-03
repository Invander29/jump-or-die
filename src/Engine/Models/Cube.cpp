#include "Cube.h"
#include "../Application.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Models;

Cube::Cube(std::shared_ptr<Managers::ShaderManager::Program> program, float size)
		: Model(program)
{
	// Prepare buffer of vertices
	const GLfloat vertices[] = {
		// front
		-1.0f * size,	-1.0f * size,	1.0f * size,
		1.0f * size,	-1.0f * size,	1.0f * size,
		1.0f * size,	1.0f * size,	1.0f * size,
		-1.0f * size,	1.0f * size,	1.0f * size,
		// top
		-1.0f * size,	1.0f * size,	1.0f * size,
		1.0f * size,	1.0f * size,	1.0f * size,
		1.0f * size,	1.0f * size,	-1.0f * size,
		-1.0f * size,	1.0f * size,	-1.0f * size,
		// back
		1.0f * size,	-1.0f * size,	-1.0f * size,
		-1.0f * size,	-1.0f * size,	-1.0f * size,
		-1.0f * size,	1.0f * size,	-1.0f * size,
		1.0f * size,	1.0f * size,	-1.0f * size,
		// bottom
		-1.0f * size,	-1.0f * size,	-1.0f * size,
		1.0f * size,	-1.0f * size,	-1.0f * size,
		1.0f * size,	-1.0f * size,	1.0f * size,
		-1.0f * size,	-1.0f * size,	1.0f * size,
		// left
		-1.0f * size,	-1.0f * size,	-1.0f * size,
		-1.0f * size,	-1.0f * size,	1.0f * size,
		-1.0f * size,	1.0f * size,	1.0f * size,
		-1.0f * size,	1.0f * size,	-1.0f * size,
		// right
		1.0f * size,	-1.0f * size,	1.0f * size,
		1.0f * size,	-1.0f * size,	-1.0f * size,
		1.0f * size,	1.0f * size,	-1.0f * size,
		1.0f * size,	1.0f * size,	1.0f * size
	};

	// Prepare buffer of normals
	const GLfloat normals[] = {
		// front
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
		// top
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		// back
		0, 0, -1,
		0, 0, -1,
		0, 0, -1,
		0, 0, -1,
		// bottom
		0, -1, 0,
		0, -1, 0,
		0, -1, 0,
		0, -1, 0,
		// left
		-1, 0, 0,
		-1, 0, 0,
		-1, 0, 0,
		-1, 0, 0,
		// right
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
	};

	const GLushort elements[] = {
		// front
		0,  1,  2,
		2,  3,  0,
		// top
		4,  5,  6,
		6,  7,  4,
		// back
		8,  9, 10,
		10, 11,  8,
		// bottom
		12, 13, 14,
		14, 15, 12,
		// left
		16, 17, 18,
		18, 19, 16,
		// right
		20, 21, 22,
		22, 23, 20
	};

	// 1. Bind Vertex Array Object
	glBindVertexArray(mVAO);

	// 2. Copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 3. Copy our index array in a element buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

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

Cube::~Cube()
{
}

void Cube::draw(Scenes::Scene* scene)
{
	Model::draw(scene);
}

void Cube::update()
{
	Input::Keyboard& keyboard = Application::instance().keyboard();
	/*if (keyboard.isKeyPressed(SDL_SCANCODE_LEFT)) {
		moveX(-3 * Core::Core::GetSpeed());
	} else if (keyboard.isKeyPressed(SDL_SCANCODE_RIGHT)) {
		moveX( 3 * Core::Core::GetSpeed());
	}

	if (keyboard.isKeyPressed(SDL_SCANCODE_UP)) {
		moveY( 3 * Core::Core::GetSpeed());
	} else if (keyboard.isKeyPressed(SDL_SCANCODE_DOWN)) {
		moveY(-3 * Core::Core::GetSpeed());
	}

	if (keyboard.isKeyPressed(SDL_SCANCODE_W)) {
		moveZ(-3 * Core::Core::GetSpeed());
	} else if (keyboard.isKeyPressed(SDL_SCANCODE_S)) {
		moveZ( 3 * Core::Core::GetSpeed());
	}*/
}
