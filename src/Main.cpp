#include "Engine/Utils/Basics.h"
#ifdef WINDOWS
#include <Windows.h>
#endif

#include "Engine/Utils/Message.h"
#include "Engine/Application.h"
#include "GameScene.h"
#include "Engine/Utils/ModelLoader.h"

using namespace Utils;

int main(int argc, char** argv) 
{
	// Create game window
	if (!Application::instance().init("JumpOrDie", 800, 600, 3, 3)) {
		return Message::error(__FILE__, __LINE__, 1, "Error while initializing game!");
	}

	// Create scene
	Scenes::spGameScene scene = std::make_shared<Scenes::GameScene>();
	Application::instance().sceneManager().set(scene);

	// Run
	if (!Application::instance().run()) {
		return Message::error(__FILE__, __LINE__, 2, "Error during game run!");
	}

	return 0;
}

#if defined(_WIN32) && !defined(_DEBUG)
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	return main(0, nullptr);
}
#endif