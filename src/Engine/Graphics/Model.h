#pragma once

#include <GL/gl3w.h>
#include <string>

#include "../Utils/Basics.h"

namespace Graphics {

	/**
	 * Class for model representation
	 */
	class Model
	{
	public:
		/**
		 * Clear memory 
		 */
		~Model();

		/**
		 * Load by it's name (from file or from memory when starts with ':')
		 */
		bool load(const std::string& name);

		/**
		 * Get models name
		 */
		const std::string& name() const { return mName; }

		/**
		 * Get ID of VAO
		 */
		GLuint vao() const { return mVAO; }

		/**
		 * Get ID of VBO
		 */
		GLuint vbo() const { return mVBO; }

		/**
		 * Get number of all vertices in model
		 */
		GLuint size() const { return mNumOfVertices; }

	private:
		std::string mName;
		GLuint mVAO = 0;
		GLuint mVBO = 0;
		GLuint mNumOfVertices = 0;
	};

	MAKE_SMART(Model);
}
