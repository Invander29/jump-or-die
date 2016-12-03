//
// Created by invander on 25.10.16.
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "../Application.h"

using namespace Scenes;

Camera::Camera(float fov, float nearPlane, float farPlane)
	: mPosition(0, 0, 0), mWorldUp(0, 1, 0), mYaw(-90.0f), mPitch(0.0f)
{
	mPerspective = glm::perspective(
			glm::radians(fov), // Field of view (30 - 90)
			1.0f * Application::instance().width() / Application::instance().height(), // Window ratio
			nearPlane,    // near
			farPlane); // far

	updateVectors();
}

void Camera::move(const glm::vec3& vector)
{
	mPosition += vector;
	updateVectors();
}

void Camera::moveRight(float x)
{
	move(glm::vec3(x, 0.0f, 0.0f));
}

void Camera::moveUp(float y)
{
	move(glm::vec3(0.0f, y, 0.0f));
}

void Camera::moveForward(float z)
{
	move(glm::vec3(0.0f, 0.0f, z));
}

void Camera::rotate(float angle, glm::vec3 vector)
{
	mYaw += vector.y * angle;
	mPitch += vector.x * angle;

	updateVectors();
}

void Camera::lookRight(float angle)
{
	rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::lookUp(float angle)
{
	rotate(angle, glm::vec3(1.0f, 0.0f, 0.0f));
}

void Camera::lookSide(float angle)
{
	rotate(angle, glm::vec3(0.0f, 0.0f, 1.0f));
}

void Camera::updateVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
	front.y = sin(glm::radians(mPitch));
	front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));

	mFront = glm::normalize(front);
	mRight = glm::normalize(glm::cross(mFront, mWorldUp));
	mUp = glm::normalize(glm::cross(mRight, mFront));

	mMatrix = mPerspective * glm::lookAt(mPosition, mPosition + mFront, mUp);
}
