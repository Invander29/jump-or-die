#pragma once

#include <GL/gl3w.h>
#include <string>

#include "../Utils/Basics.h"

namespace Graphics {

	class Model
	{
	public:
		~Model();

		bool load(const std::string& name);

		const std::string& name() const { return mName; }
		GLuint vao() const { return mVAO; }
		GLuint vbo() const { return mVBO; }
		GLuint size() const { return mNumOfVertices; }

	private:
		std::string mName;
		GLuint mVAO = 0;
		GLuint mVBO = 0;
		GLuint mNumOfVertices = 0;
	};

	MAKE_SMART(Model);
}
