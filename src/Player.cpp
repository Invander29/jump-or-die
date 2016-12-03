#include "Player.h"
#include "Engine/Input/Keyboard.h"
#include "Engine/Application.h"
#include "Engine/ModelLoader.h"
#include "Engine/Utils/Message.h"

#include <tiny_obj_loader.h>

Player::Player(std::shared_ptr<Managers::ShaderManager::Program> program)
	: Model(program)
{
	// Load from file
	/*ModelLoader loader;
	if (!loader.load("mch.obj")) {
		Utils::Message::error(__FILE__, __LINE__, "Cannot load file %s", "mch.obj");
		return;
	}*/

	using namespace tinyobj;
	using namespace Utils;

	attrib_t attrib;
	std::vector<shape_t> shapes;
	std::vector<material_t> materials;
	std::string error;

	bool ret = LoadObj(&attrib, &shapes, &materials, &error, "models/mch.obj", "models/");
	if (!ret) {
		Message::error(__FILE__, __LINE__, "Cannot load obj file %s", error.c_str());
		return;
	}

	// Load texture
	mTexture = Application::instance().resourceManager().texture("mch.png");

	// Load to GPU TODO This is not correct, just a not working example
	// 1. Bind Vertex Array Object
	glBindVertexArray(mVAO);

	// 2. Copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, attrib.vertices.size(), attrib.vertices.data(), GL_STATIC_DRAW);

	// 3. Copy our index array in a element buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shapes[0].mesh.indices.size(), shapes[0].mesh.indices.data(), GL_STATIC_DRAW);

	// 3. Then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// 2. Copy our normals array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, mNBO);
	glBufferData(GL_ARRAY_BUFFER, attrib.normals.size(), attrib.normals.data(), GL_STATIC_DRAW);

	// 3. Then set the vertex attributes pointers
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(1);

	// 2. Copy our texcoords array in a buffer for OpenGL to use
	glGenBuffers(1, &mTBO);
	glBindBuffer(GL_ARRAY_BUFFER, mTBO);
	glBufferData(GL_ARRAY_BUFFER, attrib.texcoords.size(), attrib.texcoords.data(), GL_STATIC_DRAW);

	// 3. Then set the vertex attributes pointers
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(2);

	//4. Unbind the VBO, VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Player::~Player()
{
	if (mTexture) {
		Application::instance().resourceManager().deleteTexture(mTexture->name());
	}

	if (mTBO != 0) {
		glDeleteBuffers(1, &mTBO);
	}
}

void Player::draw(Scenes::Scene* scene)
{
	Model::draw(scene);

	glBindVertexArray(mVAO);
	int size; glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void Player::update()
{
	Input::Keyboard& keyboard = Application::instance().keyboard();
	if (keyboard.isKeyTriggered(GLFW_KEY_SPACE)) {
		moveZ(-2.0f);
		mJumpPosition++;
	}
}
