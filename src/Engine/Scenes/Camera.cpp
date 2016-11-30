//
// Created by invander on 25.10.16.
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "../Application.h"

Scenes::Camera::Camera(float fov, float nearPlane, float farPlane)
{
	mPerspective = glm::perspective(
			glm::radians(fov), // Field of view (30 - 90)
			1.0f * Application::instance().width() / Application::instance().height(), // Window ratio
			nearPlane,    // near
			farPlane); // far*/

	mMatrix = mPerspective * mView;
}

void Scenes::Camera::lookAt(glm::vec3 position, glm::vec3 lookAt)
{
	mView = glm::lookAt(position, lookAt, glm::vec3(0.0f, 1.0f, 0.0f));
	mMatrix = mPerspective * mView;
}

void Scenes::Camera::move(glm::vec3 vector)
{
	mView = glm::translate(mView, vector);
	mMatrix = mPerspective * mView;
}

void Scenes::Camera::moveRight(float x)
{
	move(glm::vec3(-x, 0.0f, 0.0f));
}

void Scenes::Camera::moveUp(float y)
{
	move(glm::vec3(0.0f, -y, 0.0f));
}

void Scenes::Camera::moveForward(float z)
{
	move(glm::vec3(0.0f, 0.0f, z));
}

void Scenes::Camera::rotate(float angle, glm::vec3 vector)
{
	mView = glm::rotate(mView, angle, vector);
	mMatrix = mPerspective * mView;
}

void Scenes::Camera::lookRight(float angle)
{
	rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Scenes::Camera::lookUp(float angle)
{
	rotate(-angle, glm::vec3(1.0f, 0.0f, 0.0f));
}

void Scenes::Camera::lookSide(float angle)
{
	rotate(angle, glm::vec3(0.0f, 0.0f, 1.0f));
}
