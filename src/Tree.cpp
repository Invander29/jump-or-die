#include "Tree.h"
#include "Engine/Application.h"
#include "Images/Images.h"

extern Image ImageTree;

Tree::Tree(std::shared_ptr<Managers::ShaderManager::Program> program)
	: ModelObj(program, ":Tree", &ImageTree)
{
	mScale = glm::vec3(0.25f);
}
