#pragma once

#include "Engine/Models/CubeColor.h"

class Tree : public Models::CubeColor
{
public:
	explicit Tree(GLuint program);
};

MAKE_SMART(Tree);