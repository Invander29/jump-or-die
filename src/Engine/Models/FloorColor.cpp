//
// Created by invander on 25.10.16.
//

#include "FloorColor.h"

Models::FloorColor::FloorColor(GLuint program, float width, float length, float height, float r, float g, float b)
		: Floor(program, width, length, height), mR(r), mG(g), mB(b)
{
	bindUniform(mProgram, mUniColor, "v_color");
}

void Models::FloorColor::draw(const glm::mat4 &view)
{
	glUseProgram(mProgram);

	// Set color
	glUniform3f(mUniColor, mR, mG, mB);

	// Draw as usual
	Floor::draw(view);
}
