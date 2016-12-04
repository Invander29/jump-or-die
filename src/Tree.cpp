#include "Tree.h"

Tree::Tree(std::shared_ptr<Managers::ShaderManager::Program> program)
	: ModelObj(program, "strom", "str")
{
	mScale = glm::vec3(0.25f);
}
