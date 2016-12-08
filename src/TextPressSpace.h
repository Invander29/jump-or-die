#pragma once
#include "Engine/Models/ModelObj.h"

class TextPressSpace : public Models::ModelObj
{
public:
	explicit TextPressSpace(const std::shared_ptr<Managers::ShaderManager::Program>& program);

	void draw(Scenes::Scene* scene) override;
	void setVisibility(bool value) { mVisible = value; }
	bool getVisibility() const { return mVisible; }


private:
	bool mVisible;
};

MAKE_SMART(TextPressSpace);