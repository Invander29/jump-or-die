#include "Player.h"
#include "Engine/Input/Keyboard.h"
#include "Engine/Application.h"

Player::Player(std::shared_ptr<Managers::ShaderManager::Program> program)
	: CubeColor(program, 1.0f, 1.0f, 1.0f, 1.0f)
{
}

Player::~Player()
{
}

void Player::draw(Scenes::Scene* scene)
{
	CubeColor::draw(scene);
}

void Player::update()
{
	Input::Keyboard& keyboard = Application::instance().keyboard();
	if (keyboard.isKeyTriggered(GLFW_KEY_SPACE)) {
		moveZ(-2.0f);
		mJumpPosition++;
	}
}
