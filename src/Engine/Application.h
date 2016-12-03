#pragma once

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "Utils/Basics.h"

#include "Managers/SceneManager.h"
#include "Managers/ShaderManager.h"
#include "Managers/ResourceManager.h"

#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "Lighting/LightTypes.h"

/**
 * Basic class for this engine. It creates window and manages all managers. Use as singleton.
 */
class Application {
	SINGLETON(Application);

public:
	/**
	* Create window
	* @param width window size
	* @param height window size
	* @return 0 if success
	*/
	bool init(const std::string& title, int width, int height, int glMajor = -1, int glMinor = -1);

	/**
	* Start engine
	* @return 0 if no error
	*/
	bool run();

	/**
	 * Returns with of current window
	 * @return with of current window
	 */
	int width() const { return mWidth; }

	/**
	 * Returns height of current window
	 * @return height of current window
	 */
	int height() const { return mHeight; }

	/**
	 * Get frequence of game loop (for instance 1 / 100 per second)
	 * @return frequence of game loop
	 */
	float speed() const { return static_cast<float>(mSpeed); }

	/**
	 * Get SceneManager
	 * @return SceneManager
	 */
	Managers::SceneManager& sceneManager() { return mSceneManager; }

	/**
	 * Get ShaderManager
	 * @return ShaderManager
	 */
	Managers::ShaderManager& shaderManager() { return mShaderManager; }

	/**
	 * Get ResourceManager
	 * @return ResurceManager
	 */
	Managers::ResourceManager& resourceManager() { return mResourceManager; }

	/**
	 * Get Keyboard
	 * @return Keyboard
	 */
	Input::Keyboard& keyboard() { return mKeyboard; }

	/**
	 * Get Mouse
	 * @return Mouse
	 */
	Input::Mouse& mouse() { return mMouse; }

	void setLightingMode(Lighting::Type lightMode) { mLightingMode = lightMode; }
	Lighting::Type lightingMode() const { return mLightingMode; }

private:
	// Inits
	bool initWindow();
	bool initOpenGL();

	// Events
	void onError(int error, const char* description);
	void onResize(int width, int height);

	/**
	 * Stop game loop
	 */
	void stop() { mRunning = false; }

	/**
	 * Release resources
	 */
	void release();


	double mSpeed = 1.0 / 100.0;

	int mWidth = -1;
	int mHeight = -1;
	int mMajorVersion = -1;
	int mMinorVersion = -1;

	bool mInited = false;
	bool mRunning = false;

	std::string mWindowTitle;
	GLFWwindow* mWindow = nullptr;

	Lighting::Type mLightingMode = Lighting::Type::NONE;

	Managers::SceneManager mSceneManager;
	Managers::ShaderManager mShaderManager;
	Managers::ResourceManager mResourceManager;

	Input::Keyboard mKeyboard;
	Input::Mouse mMouse;
};