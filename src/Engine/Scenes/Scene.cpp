#include "Scene.h"
#include "../Models/Model.h"
#include "../Core.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace Scenes;
using namespace Models;

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
		object->draw(mCamera.getMatrix());
	}
}

void Scene::show()
{
	Utils::debug("Scene show");
}

void Scene::resume()
{
	Utils::debug("Scene resume");
	mPause = false;
}

void Scene::pause()
{
	Utils::debug("Scene pause");
	mPause = true;
}

void Scene::hide()
{
	Utils::debug("Scene hide");
}
