#pragma once

#include "Engine/Models/ModelObj.h"

/**
* Abstract Car
*/
class Car : public Models::ModelObj
{
public:

	/**
	* Konstruktor objektu, pripadne nastavenia scale a rotacie a implicitnych hodnot.
	* @param program program
	* @param fromRight true ak je smer zprava, false ak zlava
	* @param delayTime cas pockania na zobrazenie
	* @param waitTime cas oneskorenia
	* @param mSpeed rychlost pohybu
	*/
	explicit Car(std::shared_ptr<Managers::ShaderManager::Program> program, bool fromRight, float delayTime, float waitTime, float mSpeed);

	/**
	* Tato metoda sluzi na akcie pri prekreslovani sceny pri kazdej iteracii.
	*/
	void update() override;

	/**
	* Tato metoda sluzi na vykreslenie.
	* @param scene scena, do ktorej sa vykresluje
	*/
	void draw(Scenes::Scene* scene) override;
	
	/**
	* Zavolanim tejto metody dame objektu vediet ze je koniec hry - treba sa zastavit.
	*/
	void gameover();

protected:
	static const float AREA_X;

	bool mFromRight;
	bool mVisible;
	bool stopped;

	float mTime;
	float mWaitTime;
	float mSpeed;
};

MAKE_SMART(Car);