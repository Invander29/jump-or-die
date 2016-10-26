#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define WINDOWS
#include <Windows.h>
#else
// Linux specific
#define UNIX
#endif

#include "Engine/Utils/Utils.h"
#include "Engine/Core.h"
#include "GameScene.h"

int main(int argc, char** argv) 
{
	// Open debug console
#if defined(_DEBUG) && defined(WINDOWS)
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	std::cout << "Console for debug" << std::endl;
#endif

	// Create game window
	int errorCode = 0;
	if ((errorCode = Core::Create(800, 600)) != 0) {
		Utils::error("Error while initializing game!");
		return errorCode;
	}

	// Create scene
	Scenes::spGameScene scene = std::make_shared<Scenes::GameScene>();
	Core::GetSceneManager().set(scene);

	// Run
	if ((errorCode = Core::Run()) != 0) {
		Utils::error("Error during game run!");
		return errorCode;
	}

	return 0;
}
