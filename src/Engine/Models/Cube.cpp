#include "Cube.h"
#include "../Core.h"
#include "../Managers/ResourceManager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <lodepng.h>

using namespace Models;

Cube::Cube(GLuint program, float size)
		: Model(program)
{
	// Bind attributes
	bindAttrib(mProgram, mAttrCoord3d, "coord3d");

	// Bind uniforms
	bindUniform(mProgram, mUniMvp, "mvp");

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

	glGenBuffers(1, &mVboVertices);
	glBindBuffer(GL_ARRAY_BUFFER, mVboVertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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

	glGenBuffers(1, &mIboElements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIboElements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
}

Cube::~Cube()
{
	//glDeleteProgram(mProgram);
	glDeleteBuffers(1, &mVboVertices);
	glDeleteBuffers(1, &mIboElements);
}

void Cube::draw(const glm::mat4& view)
{
	glUseProgram(mProgram);

	// Move object to location
	glm::mat4 mvp = glm::translate(view, mPosition);
	glUniformMatrix4fv(mUniMvp, 1, GL_FALSE, glm::value_ptr(mvp));

	// Draw it
	glBindBuffer(GL_ARRAY_BUFFER, mVboVertices);
	glEnableVertexAttribArray((GLuint)mAttrCoord3d);
	glVertexAttribPointer(
			(GLuint)mAttrCoord3d, // attribute
			3, // number of elements per vertex
			GL_FLOAT, // type of element
			GL_FALSE, // take value as-is
			0, // next data appears every 5 floats
			0); // offset of first element
}

void Cube::update()
{
	Input::Keyboard& keyboard = Core::Core::GetKeyboard();
	if (keyboard.isKeyPressed(SDL_SCANCODE_LEFT)) {
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
	}
}
