//
// Created by invander on 22.10.16.
//

#include "SceneManager.h"
#include "../Application.h"

using namespace Managers;

Scenes::spScene SceneManager::set(Scenes::spScene scene)
{
	// Stop old scene
	if (mCurrentScene) {
		if (!mCurrentScene->isPaused()) {
			mCurrentScene->pause();
		}
		mCurrentScene->hide();
	}

	// Replace with new one
	mCurrentScene = scene;
	if (mCurrentScene) {
		mCurrentScene->show();
		mCurrentScene->resume();
	}

	return mCurrentScene;
}

Scenes::spScene SceneManager::active() const {
	return mCurrentScene;
}

void SceneManager::update()
{
	/**
	 * Common settings
	 */
	Application& app = Application::instance();
	if (app.keyboard().isKeyTriggered(GLFW_KEY_1)) {
		app.setLightingMode(Lighting::Type::NONE);
	} 
	else if (app.keyboard().isKeyTriggered(GLFW_KEY_2)) {
		app.setLightingMode(Lighting::Type::PHONG);
	}


	if (mCurrentScene) {
		mCurrentScene->update();
	}
}

void SceneManager::draw()
{
	if (mCurrentScene) {
		mCurrentScene->draw();
	}
}
