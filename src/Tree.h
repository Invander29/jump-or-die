#pragma once

#include "Engine/Models/ModelObj.h"

/**
* Abstract Tree
*/
class Tree : public Models::ModelObj
{
public:
	/**
	* Konstruktor objektu Tree
	* @param program program ID for OpenGL
	*/
	explicit Tree(std::shared_ptr<Managers::ShaderManager::Program> program);
};

MAKE_SMART(Tree);