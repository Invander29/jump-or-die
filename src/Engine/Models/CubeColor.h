//
// Created by invander on 24.10.16.
//

#pragma once

#include "Cube.h"

namespace Models {

	/**
	 * Cube made of single color
	 */
	class CubeColor : public Cube {
	public:
		/**
		 * Create new colored cube
		 * @param program program ID for OpenGL
		 * @param size size of cube
		 * @param r Red
		 * @param g Green
		 * @param b Blue
		 */
		CubeColor(std::shared_ptr<Managers::ShaderManager::Program> program, float size, float r, float g, float b);
		~CubeColor();

		virtual void draw(Scenes::Scene* scene) override;

	private:
		Uniform mUniColor;
		float mR, mG, mB;
	};

	MAKE_SMART(CubeColor);
}