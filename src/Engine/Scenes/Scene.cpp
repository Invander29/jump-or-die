#include "Scene.h"

#include "../Models/ModelObject.h"
#include "../Application.h"
#include "../Utils/Message.h"

using namespace Scenes;
using namespace Models;
using namespace Utils;

Scene::Scene()
	: mCamera(45.0f, 0.1f, 100.0f)
{
}


Scene::~Scene()
{
}

Models::spGameObject Scene::add(Models::spGameObject object) {
	if (object) {
		mObjects.push_back(object);
	}
	return object;
}

Camera &Scene::setCamera(Camera &camera) {
	mCamera = camera;
	return camera;
}

void Scene::update()
{
	if (isPaused()) {
		return;
	}

	for (spGameObject object : mObjects) {
		object->update();
	}
}

void Scene::draw()
{
	for (spGameObject object : mObjects) {
		object->draw(this);
	}
}

void Scene::show()
{
	// If paused, resume
	if (isPaused()) {
		resume();
	}

	Message::debug("Scene show");
}

void Scene::resume()
{
	Message::debug("Scene resume");
	mPause = false;
}

void Scene::pause()
{
	Message::debug("Scene pause");
	mPause = true;
}

void Scene::hide()
{
	Message::debug("Scene hide");

	// Pause if not paused yet
	if (!isPaused()) {
		pause();
	}

	// Clear objects
	mObjects.clear();
}
