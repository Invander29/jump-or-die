#pragma once

#include "Engine/Models/ModelObj.h"

/**
* Abstract Player
*/
class Player : public Models::ModelObj
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
	
	void gameover();
	int jumpPosition() const { return mJumpPosition; }

private:
	bool stopped;
	int mJumpPosition = 0;
	int jumpAnimation = 0;
	static const int ANIM_STEPS = 20;
};

MAKE_SMART(Player);
