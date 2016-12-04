#include "Player.h"

#include <cmath>
#include <tiny_obj_loader.h>

#include "Engine/Input/Keyboard.h"
#include "Engine/Application.h"
#include "Engine/Utils/Message.h"
#include "Engine/Utils/ModelLoader.h"


Player::Player(std::shared_ptr<Managers::ShaderManager::Program> program)
	: ModelObj(program, "mch", "mch")
{
	mScale = glm::vec3(0.5f);
}

Player::~Player()
{
}

void Player::draw(Scenes::Scene* scene)
{
	ModelObj::draw(scene);
}

void Player::update()
{
	Input::Keyboard& keyboard = Application::instance().keyboard();
	if (keyboard.isKeyTriggered(GLFW_KEY_SPACE)) {
		if (jumpAnimation > -1) //ak sa nestihne dokoncit animacia
		{
			moveZ(-2.0 / ANIM_STEPS * (ANIM_STEPS - jumpAnimation));
			setZ(round(z()));
			setY(0.0);
		}
		jumpAnimation = 0;
		mJumpPosition++;
	}
	if (jumpAnimation > -1 && jumpAnimation<ANIM_STEPS) //animacia skoku
	{
		moveZ(-2.0/ ANIM_STEPS);
		moveY(jumpAnimation<(ANIM_STEPS/2) ? (4.0 / (ANIM_STEPS / 2)) : (-4.0 / (ANIM_STEPS / 2)));
		jumpAnimation++;
	}
	else
	{
		jumpAnimation = -1;
		setZ(round(z()));
		setY(0.0);
	}
}
