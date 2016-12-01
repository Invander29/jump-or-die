#pragma once

#include "Engine/Models/CubeColor.h"

/**
* Abstract Player
*/
class Player : public Models::CubeColor
{
public:
	/**
	* Create new Player
	* @param program program ID for OpenGL
	*/
	explicit Player(GLuint program);
	virtual ~Player();

	void draw(const glm::mat4& view) override;
	void update() override;

	int jumpPosition() const { return mJumpPosition; }

private:
	int mJumpPosition = 0;
	int jumpAnimation;
	static const int ANIM_STEPS = 20;
};

MAKE_SMART(Player);
