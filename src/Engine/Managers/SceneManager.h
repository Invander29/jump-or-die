//
// Created by invander on 22.10.16.
//

#pragma once

#include "../Scenes/Scene.h"

namespace Managers {

	/**
	 * Class for managing scene (switch to another, ...)
	 */
	class SceneManager {
	public:
		/**
		 * Set new scene
		 * @param scene existing scene
		 * @return inserted scene
		 */
		Scenes::spScene set(Scenes::spScene scene);

		/**
		 * Get active scene
		 * @return active scene
		 */
		Scenes::spScene active() const;

		/**
		 * Update active scene
		 */
		void update();

		/**
		 * Draw active scene
		 */
		void draw();

	private:
		Scenes::spScene mCurrentScene;
	};

}