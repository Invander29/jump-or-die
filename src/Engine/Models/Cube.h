#pragma once

#include <GL/glew.h>
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
		Cube(GLuint program, float size);

		virtual ~Cube() = 0;

		virtual void draw(const glm::mat4& view) override;

		virtual void update() override;

	protected:
		GLuint mVboVertices = 0;
		GLuint mIboElements = 0;

		GLint mAttrCoord3d = -1;
		GLint mUniMvp = -1;
	};

	MAKE_SMART(Cube);
}
