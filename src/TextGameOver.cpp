#include "TextGameOver.h"

void TextGameOver::draw(Scenes::Scene* scene)
{
	if (!mVisible) {
		return;
	}

	ModelObj::draw(scene);
}
