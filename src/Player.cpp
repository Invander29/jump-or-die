#include "Player.h"
#include "Engine/Input/Keyboard.h"
#include "Engine/Application.h"

Player::Player(GLuint program)
	: CubeColor(program, 1.0f, 1.0f, 1.0f, 1.0f)
{
}

Player::~Player()
{
}

void Player::draw(const glm::mat4& view)
{
	CubeColor::draw(view);
}

void Player::update()
{
	Input::Keyboard& keyboard = Application::instance().keyboard();
	if (keyboard.isKeyTriggered(GLFW_KEY_SPACE)) {
		moveZ(-2.0f);
		mJumpPosition++;
	}
}
