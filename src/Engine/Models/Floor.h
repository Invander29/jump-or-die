//
// Created by invander on 24.10.16.
//

#pragma once

#include <GL/glew.h>
#include "Model.h"

namespace Models {

	/**
	 * Abstract floor oject
	 */
	class Floor : public Model {
	public:
		/**
		 * Create new floor
		 * @param program program ID for OpenGL
		 * @param width width of floor
		 * @param length length of floor
		 * @param height level of floor
		 */
		Floor(GLuint program, float width, float length, float height);

		virtual ~Floor() = 0;

		virtual void draw(const glm::mat4 &view) override;

		virtual void update() override;

	protected:
		GLuint mVboVertices = 0;
		GLint mAttrCoord3d = -1;
		GLint mUniMvp = -1;

		float mWidth, mHeight, mLength;
	};

	MAKE_SMART(Floor);
}

