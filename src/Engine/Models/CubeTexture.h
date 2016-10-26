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
		CubeTexture(GLuint program, float size, GLuint texture);
		~CubeTexture();

		virtual void draw(const glm::mat4& view) override;

	private:
		GLuint mVboTexcoords = 0;
		GLuint mTextureId = 0;

		GLint mAttrTexcoord = -1;
		GLint mUniTexture = -1;
	};

	MAKE_SMART(CubeTexture);
}