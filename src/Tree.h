#pragma once

#include "Engine/Models/CubeColor.h"

class Tree : public Models::CubeColor
{
public:
	explicit Tree(std::shared_ptr<Managers::ShaderManager::Program> program);
};

MAKE_SMART(Tree);