#include "Core.h"
#include "Utils/Utils.h"
#include "Utils/Timer.h"

// OpenGL
#define GL3_PROTOTYPES 1
#include <GL/glew.h>

Core::Core()
{
}

Core::~Core()
{
	release();
}

int Core::init(int width, int height)
{
	mWidth = width;
	mHeight = height;

	// Release old state if any
	release();

	// Init subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		Utils::errorSDL("SDL_Init");
		return 1;
	}
	else {
		mInited = true;
	}

	// Open Window
	mWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		mWidth, mHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (!mWindow) {
		Utils::errorSDL("SDL_CreateWindow");
		release();
		return 3;
	}

	// Create opengl context
	mMainContext = SDL_GL_CreateContext(mWindow);

	// Old deprecated code is disabled
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// Version of OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// Enable Double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// Enable transparency
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Depth buffer
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	// Cull face (triangles rotation)
	glEnable(GL_CULL_FACE);

	// Sync with monitor framerate
	if (SDL_GL_SetSwapInterval(1) < 0) {
		Utils::errorSDL("SDL_GL_SetSwap");
		// TODO Handle this if not supported
	}

	// Init GLEW
	glewExperimental = GL_TRUE;
	GLenum glewStatus = glewInit();
	if (glewStatus != GLEW_OK) {
		std::cerr << "Error: " << glewGetErrorString(glewStatus) << std::endl;
		release();
		return 4;
	}

    // Init managers

	return 0;
}

int Core::run()
{
	// Check if inited
	if (!mInited) {
		Utils::error("Game::run not inited yet!");
		return 1;
	}

	// Fixed timestep
	// http://gafferongames.com/game-physics/fix-your-timestep/
	Utils::Timer timer;
	double second = 0.0;
	double elapsed = 0.0;
	int fps = 0;
	int sim = 0;
	mRunning = true;

	while (mRunning) {
		// Process events
		processEvents();

		// Run updates with fixed time
		double delta = timer.getDelta();
		elapsed += delta;
		while (elapsed >= mSpeed) {
			elapsed -= mSpeed;
			++sim;
			mSceneManager.update();
		}
		
		// Clear
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw
		mSceneManager.draw();

		// Show frame
		++fps;
		SDL_GL_SwapWindow(mWindow);

		// Show info
		second += delta;
		if (second > 5.0) {
			Utils::debug("FPS: %d\tSIM: %d\tSEC: %f", fps / 5, sim / 5, second);
			sim = fps = 0;
			second -= 5.0;
		}
	}

	return 0;
}

void Core::release()
{
	// Release scene
	GetSceneManager().set(nullptr);

	if (mMainContext) {
		SDL_GL_DeleteContext(mMainContext);
		mMainContext = nullptr;
	}

	if (mWindow) {
		SDL_DestroyWindow(mWindow);
		mWindow = nullptr;
	}

	if (mInited) {
		mInited = false;
		SDL_Quit();
	}
}

void Core::processEvents()
{
	mKeyboard.update();
	mMouse.update();

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		mMouse.receiveEvent(event);

		switch (event.type) {
			case SDL_QUIT:
				stop();
				break;

			case SDL_WINDOWEVENT: {
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
					onResize(event.window.data1, event.window.data2);
			}
		} break;
		default:
			break;
		}
	}
}

void Core::onResize(int width, int height)
{
	mWidth = width;
	mHeight = height;
	glViewport(0, 0, width, height);
}
