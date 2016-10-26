//
// Created by invander on 22.10.16.
//

#include "SceneManager.h"

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

Scenes::spScene SceneManager::get() const {
	return mCurrentScene;
}

void SceneManager::update()
{
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
