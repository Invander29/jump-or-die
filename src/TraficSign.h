#pragma once

#include "Engine/Models/CubeColor.h"

class TraficSign : public Models::CubeColor
{
public:
	explicit TraficSign(GLuint program);
};

MAKE_SMART(TraficSign);