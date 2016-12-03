//
// Created by invander on 24.10.16.
//

#pragma once

#include "Cube.h"

namespace Models {

	/**
	 * Simple cube with single texture
	 */
	class CubeTexture : public Cube {
	public:
		/**
		 * Create new cube with texture
		 * @param program program ID for OpenGL
		 * @param size size of cube
		 * @param texture texture ID for OpenGL
		 */
		CubeTexture(std::shared_ptr<Managers::ShaderManager::Program> program, float size, GLuint texture);
		~CubeTexture();

		virtual void draw(Scenes::Scene* scene) override;

	private:
		GLuint mVboTexcoords = 0;
		GLuint mTextureId = 0;
		Uniform mUniTexture;
	};

	MAKE_SMART(CubeTexture);
}