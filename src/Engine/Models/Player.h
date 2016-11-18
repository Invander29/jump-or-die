#pragma once

#include <GL/glew.h>
#include <vector>
#include "GameObject.h"
#include "Model.h"

namespace Models {

	/**
	* Abstract Player
	*/
	class Player : public Model
	{
	public:
		/**
		* Create new Player
		* @param program program ID for OpenGL
		* @param size size of Player
		*/
		Player(GLuint program, float size);

		virtual ~Player() = 0;

		virtual void draw(const glm::mat4& view) override;

		virtual void update() override;

	protected:
		GLuint mVboVertices = 0;
		GLuint mIboElements = 0;

		GLint mAttrCoord3d = -1;
		GLint mUniMvp = -1;
	};

	MAKE_SMART(Player);
}
