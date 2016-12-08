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
	
	/**
	* Destruktor objektu Player
	*/
	virtual ~Player();

	/**
	* Tato metoda sluzi na vykreslenie.
	* @param scene scena, do ktorej sa vykresluje
	*/
	void draw(Scenes::Scene* scene) override;

	/**
	* Tato metoda sluzi na akcie pri prekreslovani sceny pri kazdej iteracii.
	*/
	void update() override;
	
	/**
	* Zavolanim tejto metody dame objektu vediet ze je koniec hry - treba zakazat dalsie skakanie.
	*/
	void gameover();

	/**
	* Tato metoda vrati poziciu.
	* @return pozicia hraca
	*/
	int jumpPosition() const { return mJumpPosition; }

private:
	bool stopped;
	int mJumpPosition = 0;
	int jumpAnimation = 0;
	static const int ANIM_STEPS = 20;
};

MAKE_SMART(Player);
