//
// Created by invander on 24.10.16.
//

#pragma once

#include "Player.h"

namespace Models {

	/**
	* Simple Player with single texture
	*/
	class PlayerTexture : public Player {
	public:
		/**
		* Create new Player with texture
		* @param program program ID for OpenGL
		* @param size size of Player
		* @param texture texture ID for OpenGL
		*/
		PlayerTexture(GLuint program, float size, GLuint texture);
		~PlayerTexture();

		virtual void draw(const glm::mat4& view) override;

	private:
		GLuint mVboTexcoords = 0;
		GLuint mTextureId = 0;

		GLint mAttrTexcoord = -1;
		GLint mUniTexture = -1;
	};

	MAKE_SMART(PlayerTexture);
}