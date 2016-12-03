//
// Created by invander on 25.10.16.
//

#include "FloorColor.h"

Models::FloorColor::FloorColor(std::shared_ptr<Managers::ShaderManager::Program> program, float width, float length, float height, float r, float g, float b)
		: Floor(program, width, length, height), mR(r), mG(g), mB(b)
{
	bindUniform(mProgram, mUniColor, "color");
}

void Models::FloorColor::draw(Scenes::Scene* scene)
{
	Floor::draw(scene);
	glUniform3f(mUniColor(), mR, mG, mB);

	glBindVertexArray(mVAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindVertexArray(0);
}
