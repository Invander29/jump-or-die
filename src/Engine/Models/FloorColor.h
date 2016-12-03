//
// Created by invander on 25.10.16.
//

#pragma once

#include "Floor.h"

namespace Models {

	/**
	 * Single color floor
	 */
	class FloorColor : public Floor {
	public:
		/**
		 * Create new floor
		 * @param program program ID for OpenGL
		 * @param width width of floor
		 * @param length length of floor
		 * @param height level of floor
		 * @param r Red
		 * @param g Green
		 * @param b Blue
		 */
		FloorColor(std::shared_ptr<Managers::ShaderManager::Program> program, float width, float length, float height, float r, float g, float b);

		virtual void draw(Scenes::Scene* scene) override;

	private:
		Uniform mUniColor;
		float mR, mG, mB;
	};

	MAKE_SMART(FloorColor);
}