#pragma once

#include <GL/gl3w.h>
#include <vector>
#include "GameObject.h"
#include "Model.h"

namespace Models {

	/**
	 * Abstract cube
	 */
	class Cube : public Model
	{
	public:
		/**
		 * Create new cube
		 * @param program program ID for OpenGL
		 * @param size size of cube
		 */
		Cube(std::shared_ptr<Managers::ShaderManager::Program> program, float size);

		virtual ~Cube() = 0;

		virtual void draw(Scenes::Scene* scene) override;

		virtual void update() override;
	};

	MAKE_SMART(Cube);
}
