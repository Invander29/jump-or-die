//
// Created by invander on 25.10.16.
//

#pragma once

#include "Floor.h"

namespace Models {

	/**
	 * Simple texture floor
	 */
	class FloorTexture : public Floor {
	public:
		/**
		 * Create new floor
		 * @param program program ID for OpenGL
		 * @param width width of floor
		 * @param length length of floor
		 * @param height level of floor
		 * @param texture texture ID for OpenGL
		 */
		FloorTexture(GLuint program, float width, float length, float height, GLuint texture);

		virtual void draw(const glm::mat4 &view) override;

	private:
		GLuint mVboTexcoords = 0;
		GLuint mTextureId = 0;

		GLint mAttrTexcoord = -1;
		GLint mUniTexture = -1;
	};

	MAKE_SMART(FloorTexture);
}