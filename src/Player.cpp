#include "Player.h"

#include <cmath>
#include <tiny_obj_loader.h>

#include "Engine/Application.h"
#include "Engine/Input/Keyboard.h"
#include "Engine/Application.h"
#include "Engine/Utils/ModelLoader.h"
#include "Images/Images.h"

extern Image ImageMch;

Player::Player(std::shared_ptr<Managers::ShaderManager::Program> program)
	: ModelObj(program, ":Mch", &ImageMch)
{
	jumpAnimation = -1;
	stopped = false;
	mScale = glm::vec3(0.5f);
}

Player::~Player()
{
}


void Player::gameover()
{
	stopped = true;

}

void Player::draw(Scenes::Scene* scene)
{
	ModelObj::draw(scene);
}

void Player::update()
{
	Input::Keyboard& keyboard = Application::instance().keyboard();
	if (keyboard.isKeyTriggered(GLFW_KEY_SPACE) && !stopped) {
		if (jumpAnimation > -1) //ak sa nestihne dokoncit animacia
		{
			moveZ(-2.0f / ANIM_STEPS * (ANIM_STEPS - jumpAnimation));
			setZ(round(z()));
			setY(0.0);
		}
		jumpAnimation = 0;
		mJumpPosition++;
	}
	if (jumpAnimation > -1 && jumpAnimation<ANIM_STEPS) //animacia skoku
	{
		moveZ(-2.0f / ANIM_STEPS);
		moveY(jumpAnimation<(ANIM_STEPS/2) ? (4.0f / (ANIM_STEPS / 2)) : (-4.0f / (ANIM_STEPS / 2)));
		jumpAnimation++;
	}
	else
	{
		jumpAnimation = -1;
		setZ(round(z()));
		setY(0.0);
	}
}

