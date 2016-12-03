#pragma once

#include <memory>
#include <vector>

#include "../Utils/Basics.h"
#include "../Models/GameObject.h"
#include "Camera.h"
#include "../Lighting/Light.h"

namespace Scenes {

	/**
	 * Abstract class for managing game objects, use it as a parent
	 */
	class Scene {
	public:
		explicit Scene();
		virtual ~Scene() = 0;

		/**
		 * True if paused
		 * @return true if paused
		 */
		bool isPaused() const { return mPause; }

		/**
		 * Add game object to scene
		 * @param object Game object
		 * @return Smart pointer to game object
		 */
		Models::spGameObject add(Models::spGameObject object);

		/**
		 * Set camera to scene
		 * @param camera camera object
		 * @return Reference to camera
		 */
		Camera& setCamera(Camera& camera);

		/**
		 * Get camera from scene
		 * @return Reference to camera
		 */
		Camera& camera() { return mCamera; }

		Lighting::Light& light() { return mLight; }
		const Lighting::Light& light() const { return mLight; }

		/**
		 * Called when scene needs to prepare objects
		 */
		virtual void show();        // Prepare objects

		/**
		 * Called after show or when scene change state to "not paused"
		 */
		virtual void resume();      // Start

		/**
		 * Called every simulation frame
		 */
		virtual void update();      // Update objects

		/**
		 * Called every drawing frame
		 */
		virtual void draw();        // Draw Objects

		/**
		 * Called when scene should be paused
		 */
		virtual void pause();       // Stop

		/**
		 * Called for deleting objects
		 */
		virtual void hide();        // Release data

	protected:
		bool mPause = true;
		std::vector<Models::spGameObject> mObjects;
		Camera mCamera;
		Lighting::Light mLight;
	};

	// Make as smart pointer
	MAKE_SMART(Scene);

}
