#pragma once
#include "Engine/Models/ModelObj.h"

/**
* Abstract TextStart
*/
class TextStart : public Models::ModelObj
{
public:

	/**
	* Konstruktor objektu, pripadne nastavenia scale a rotacie.
	* @param program program
	*/
	explicit TextStart(const std::shared_ptr<Managers::ShaderManager::Program>& program);

	/**
	* Tato metoda sluzi na vykreslenie.
	* @param scene scena, do ktorej sa vykresluje
	*/
	void draw(Scenes::Scene* scene) override;

	/**
	* Tato metoda nastavi viditelnost daneho objektu.
	* @param value true ak je viditelny, false ak nie je viditelny
	*/
	void setVisibility(bool value) { mVisible = value; }

	/**
	* Tato metoda vrati viditelnost daneho objektu.
	* @return true ak je viditelny, false ak nie je viditelny
	*/
	bool getVisibility() const { return mVisible; }


private:
	bool mVisible;
};

MAKE_SMART(TextStart);