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
		CubeColor(GLuint program, float size, float r, float g, float b);
		~CubeColor();

		virtual void draw(const glm::mat4& view) override;

	private:
		GLint mUniColor = -1;
		float mR, mG, mB;
	};

	MAKE_SMART(CubeColor);
}