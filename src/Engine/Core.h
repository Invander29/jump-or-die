#pragma once

#include <SDL2/SDL.h>
#include "Scenes/Scene.h"
#include "Managers/SceneManager.h"
#include "Managers/ShaderManager.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "Managers/ResourceManager.h"

/**
 * Basic class for this engine. It creates window and manages all managers. Use as singleton.
 */
class Core {
public:
	// Singleton
	static Core &getInstance() {
		static Core instance;
		return instance;
	}

	// Singleton
	Core(Core const &) = delete;
	// Singleton
	void operator=(Core const &) = delete;

	/**
	 * Returns with of current window
	 * @return with of current window
	 */
	static int Width() { return getInstance().mWidth; }

	/**
	 * Returns height of current window
	 * @return height of current window
	 */
	static int Height() { return getInstance().mHeight; }

	/**
	 * Create new window with specific size
	 * @param with size of window
	 * @param height size of window
	 * @return 0 if success
	 */
	static int Create(int with, int height) { return getInstance().init(with, height); }

	/**
	 * Start this engine
	 * @return non-zero if error
	 */
	static int Run() { return getInstance().run(); }

	/**
	 * Get frequence of game loop (for instance 1 / 100 per second)
	 * @return frequence of game loop
	 */
	static float GetSpeed() { return static_cast<float>(getInstance().mSpeed); }

	/**
	 * Get SceneManager
	 * @return SceneManager
	 */
	static Managers::SceneManager& GetSceneManager() { return getInstance().mSceneManager; }

	/**
	 * Get ShaderManager
	 * @return ShaderManager
	 */
	static Managers::ShaderManager& GetShaderManager() { return getInstance().mShaderManager; }

	/**
	 * Get ResourceManager
	 * @return ResurceManager
	 */
	static Managers::ResourceManager& GetResourceManager() { return getInstance().mResourceManager; }

	/**
	 * Get Keyboard
	 * @return Keyboard
	 */
	static Input::Keyboard& GetKeyboard() { return getInstance().mKeyboard; }

	/**
	 * Get Mouse
	 * @return Mouse
	 */
	static Input::Mouse& GetMouse() { return getInstance().mMouse; }

private:
	/**
	 *  Private constructor
	 */
	explicit Core();

	/**
	 * Destructor for engine
	 */
	~Core();

	/**
	 * Create window
	 * @param width window size
	 * @param height window size
	 * @return 0 if success
	 */
	int init(int width, int height);

	/**
	 * Start engine
	 * @return 0 if no error
	 */
	int run();

	/**
	 * Stop game loop
	 */
	void stop() { mRunning = false; }

	/**
	 * Release resources
	 */
	void release();

	/**
	 * Process resources
	 */
	void processEvents();

	/**
	 * Process window resize event
	 */
	void onResize(int width, int height);

	/** Game loop frequence */
	double mSpeed = 1.0 / 100.0;
	/** Window width */
	int mWidth = -1;
	/** Window height */
	int mHeight = -1;
	/** true if window created */
	bool mInited = false;
	/** true if game loop is running */
	bool mRunning = false;
	/** Window handler */
	SDL_Window *mWindow = nullptr;
	/** Context hander */
	SDL_GLContext mMainContext = nullptr;

	Managers::SceneManager mSceneManager;
	Managers::ShaderManager mShaderManager;
	Managers::ResourceManager mResourceManager;

	Input::Keyboard mKeyboard;
	Input::Mouse mMouse;
};