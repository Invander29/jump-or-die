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
	explicit Player(std::shared_ptr<Managers::ShaderManager::Program> program);
	virtual ~Player();

	void draw(Scenes::Scene* scene) override;
	void update() override;

	int jumpPosition() const { return mJumpPosition; }

private:
	int mJumpPosition = 0;
};

MAKE_SMART(Player);
