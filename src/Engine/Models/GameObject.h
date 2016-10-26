#pragma once

#include "../Utils/Utils.h"
#include <vector>
#include <glm/glm.hpp>

namespace Models {

	/**
	 * Interface for game objects
	 */
	class GameObject {
	public:
		explicit GameObject() {};

		virtual ~GameObject() {};

		/**
		 * Update object per simulation frame
		 */
		virtual void update() = 0;

		/**
		 * Draw object per drawing frame
		 * @param view matrix of view
		 */
		virtual void draw(const glm::mat4& view) = 0;

	protected:

		/**
		 * Bint attrib from program to value
		 * @param program program ID
		 * @param attrib output for attrib to bind
		 * @param name name of variable
		 * @return true on success
		 */
		static bool bindAttrib(GLuint program, GLint &attrib, const char *name);

		/**
		 * Bind uniform from program to value
		 * @param program program ID
		 * @param attrib output for uniform to bind
		 * @param name name of uniform
		 * @return true on success
		 */
		static bool bindUniform(GLuint program, GLint &attrib, const char *name);
	};

// Make smart
	MAKE_SMART(GameObject);

}