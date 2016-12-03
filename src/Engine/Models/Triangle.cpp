#include "Triangle.h"

using namespace Models;

Triangle::Triangle(std::shared_ptr<Managers::ShaderManager::Program> program)
	: Model(program, false)
{
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	// 1. Bind Vertex Array Object
	glBindVertexArray(mVAO);
	// 2. Copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. Then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//4. Unbind the VAO
	glBindVertexArray(0);
} 

void Triangle::update()
{
}

void Triangle::draw(Scenes::Scene* scene)
{
	Model::draw(scene);

	glBindVertexArray(mVAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}
