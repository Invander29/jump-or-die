#pragma once

#include "Engine/Models/ModelObj.h"

class Tree : public Models::ModelObj
{
public:
	explicit Tree(std::shared_ptr<Managers::ShaderManager::Program> program);
};

MAKE_SMART(Tree);