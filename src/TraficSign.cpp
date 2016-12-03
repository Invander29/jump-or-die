#include "TraficSign.h"

TraficSign::TraficSign(std::shared_ptr<Managers::ShaderManager::Program> program)
	: CubeColor(program, 1.0f, 0.0f, 0.0f, 1.0f)
{
}
