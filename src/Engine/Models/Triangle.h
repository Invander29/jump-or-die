#pragma once
#include "Model.h"

namespace Models {

	class Triangle : public Models::Model
	{
	public:
		explicit Triangle(GLuint program);

		void update() override;
		void draw(const glm::mat4& view) override;
	};

	MAKE_SMART(Triangle);
}