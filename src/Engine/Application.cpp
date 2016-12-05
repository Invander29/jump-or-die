#include "Application.h"

#include "Utils/Message.h"
#include "Utils/Timer.h"
using namespace Utils;

Application::Application()
{
}

Application::~Application()
{
	release();
}

bool Application::init(const std::string& title, int width, int height, int glMajor, int glMinor)
{
	// Release if old state
	release();

	// Store values
	mWindowTitle = title;
	mWidth = width;
	mHeight = height;
	mMajorVersion = glMajor;
	mMinorVersion = glMinor;
	
	if (!initWindow()) {
		return false;
	}

	if (!initOpenGL()) {
		return false;
	}

	return true;
}

bool Application::initWindow()
{
	// Init GLFW
	glfwSetErrorCallback([](int error, const char* description)
	{
		Application::instance().onError(error, description);
	});

	if (!glfwInit()) {
		return Message::error(__FILE__, __LINE__, "Cannot init GLFW");
	}

	// Hint for GLFW
	if (mMajorVersion > 0) {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, mMajorVersion);
	}
	if (mMinorVersion > 0) {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, mMinorVersion);
	}
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Speed penalty, disable on release mode
#ifdef _DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

	// Create window
	mWindow = glfwCreateWindow(mWidth, mHeight, mWindowTitle.c_str(), nullptr, nullptr);
	if (!mWindow) {
		Message::error(__FILE__, __LINE__, "Cannot create window");
		glfwTerminate();
		return false;
	}

	// Set callbacks
	glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		switch (action) {
		case GLFW_PRESS: 
			Application::instance().keyboard().onKeyDown(key, scancode);
			break;
		case GLFW_RELEASE:
			Application::instance().keyboard().onKeyUp(key, scancode);
			break;
		default:
			break;
		}
	});

	glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double x, double y)
	{
		Application::instance().mouse().onMove(x, y);
	});

	glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods)
	{
		switch (action) {
		case GLFW_PRESS:
			Application::instance().mouse().onButtonDown(button);
			break;
		case GLFW_RELEASE:
			Application::instance().mouse().onButtonUp(button);
			break;
		default:
			break;
		}
	});

	glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height)
	{
		Application::instance().onResize(width, height);
	});

	// Some other settings
	glfwMakeContextCurrent(mWindow);
	glfwSwapInterval(1);
	return true;
}

bool Application::initOpenGL()
{
	if (gl3wInit()) {
		return Message::error(__FILE__, __LINE__, "Cannot init glew");
	}

	glViewport(0, 0, mWidth, mHeight);
	Message::debug("OpenGL %s, GLSL %s", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
	return true;
}

bool Application::run()
{
	// Check if inited
	if (!mWindow) {
		return Message::error(__FILE__, __LINE__, "Game::run not inited yet!");
	}

	// Fixed timestep
	// http://gafferongames.com/game-physics/fix-your-timestep/
	Utils::Timer timer;
	double second = 0.0;
	double elapsed = 0.0;
	int fps = 0;
	int sim = 0;
	mRunning = true;

	while (mRunning && !glfwWindowShouldClose(mWindow)) {
		// Run updates with fixed time
		double delta = timer.delta();
		elapsed += delta;
		while (elapsed >= mSpeed) {
			elapsed -= mSpeed;
			++sim;

			mSceneManager.update();
			
			// Process events
			mKeyboard.onNextFrame();
			mMouse.onNextFrame();
			glfwPollEvents();
		}
		
		// Clear
		glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);

		// Draw
		mSceneManager.draw();

		// Show frame
		++fps;
		glfwSwapBuffers(mWindow);

		// Show info
		second += delta;
		if (second > 5.0) {
			Message::debug("FPS: %d\tSIM: %d\tSEC: %f", fps / 5, sim / 5, second);
			sim = fps = 0;
			second -= 5.0;
		}
	}

	return true;
}

void Application::release()
{
	// Release scene
	sceneManager().set(nullptr);

	if (mWindow) {
		glfwDestroyWindow(mWindow);
		mWindow = nullptr;
		glfwTerminate();
	}
}


void Application::onError(int error, const char* description)
{
	Message::error(__FILE__, __LINE__, error, description);
}

void Application::onResize(int width, int height)
{
	mWidth = width;
	mHeight = height;
	glViewport(0, 0, width, height);
}
