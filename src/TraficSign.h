#pragma once

#include "Engine/Models/CubeColor.h"

class TraficSign : public Models::CubeColor
{
public:
	explicit TraficSign(std::shared_ptr<Managers::ShaderManager::Program> program);
};

MAKE_SMART(TraficSign);