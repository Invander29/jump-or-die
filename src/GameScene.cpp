#include <cstdlib>
#include <ctime>
#include "GameScene.h"
#include "Engine/Models/CubeTexture.h"
#include "Engine/Core.h"
#include "Engine/Models/Floor.h"
#include "Engine/Models/CubeColor.h"
#include "Engine/Models/FloorColor.h"
#include "Engine/Models/FloorTexture.h"
#include "Engine/Models/PlayerTexture.h"


using namespace Scenes;

GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}

void GameScene::show() {
	Scene::show();

	// Add camera object
	Camera camera(45.0f, 0.1f, 100.0f);
	camera.lookAt(glm::vec3(2.0f, 25.0f, 3.0f),  // Camera is in this position
		glm::vec3(0.0f, 0.0f, -12.0f));// Camera looks at this position)
	setCamera(camera);



	// Add objects to scene
	using namespace Models;
	using namespace Graphics;

	// Shaders for texture
	progSimpleTexture = Core::GetShaderManager().createProgram("simple_texture", "simple_texture.vs", "simple_texture.fs");
	spTexture texCube = Core::GetResourceManager().getTexture("cube.png");

	player_pos = 1;

	// Player
	player = std::make_shared<PlayerTexture>(progSimpleTexture, 0.5f, texCube->getId());
	player->setPosition(0, float(player_pos), -4);
	add(player);

	// Shaders for single color
	progSimpleColor = Core::GetShaderManager().createProgram("simple_color", "simple_color.vs", "simple_color.fs");

	texFloor = Core::GetResourceManager().getTexture("floor.png");
	texFloor->setWrapping(GL_REPEAT, GL_REPEAT);

	//Generate map
	floors.push_back(std::make_shared<FloorTexture>(progSimpleTexture, 25.0f, 1.0f, 0.0f, texFloor->getId()));
	floors.back()->setPosition(0, 0, (floors.size() - 1)*(-2.0));
	add(floors.back());
	floors.push_back(std::make_shared<FloorColor>(progSimpleColor, 25.0f, 1.0f, 0.0f, 0.6f, 0.6f, 0.6f));
	floors.back()->setPosition(0, 0, (floors.size() - 1)*(-2.0));
	add(floors.back());
	floors.push_back(std::make_shared<FloorTexture>(progSimpleTexture, 25.0f, 1.0f, 0.0f, texFloor->getId()));
	floors.back()->setPosition(0, 0, (floors.size() - 1)*(-2.0));
	add(floors.back());
	drawed_roads = 0;
	srand(int(time(NULL)));
	for (int i = 0; i < FLOORS_COUNT-3; i++)
	{
		drawOneFloor();
	}
}

void GameScene::update() {
	Scene::update();

	if (Core::GetKeyboard().isKeyPressed(SDL_SCANCODE_J)) {
		getCamera().lookRight(-3 * Core::GetSpeed());

	}
	else if (Core::GetKeyboard().isKeyPressed(SDL_SCANCODE_L)) {
		getCamera().lookRight(3 * Core::GetSpeed());
	}

	if (Core::GetKeyboard().isKeyPressed(SDL_SCANCODE_I)) {
		getCamera().lookUp(3 * Core::GetSpeed());

	}
	else if (Core::GetKeyboard().isKeyPressed(SDL_SCANCODE_K)) {
		getCamera().lookUp(-3 * Core::GetSpeed());
	}

	if (Core::GetKeyboard().isKeyPressed(SDL_SCANCODE_O)) {
		getCamera().lookSide(3 * Core::GetSpeed());

	}
	else if (Core::GetKeyboard().isKeyPressed(SDL_SCANCODE_P)) {
		getCamera().lookSide(-3 * Core::GetSpeed());
	}

	if (Core::GetKeyboard().isKeyPressed(SDL_SCANCODE_A)) {
		getCamera().moveRight(3 * Core::GetSpeed());

	}
	else if (Core::GetKeyboard().isKeyPressed(SDL_SCANCODE_D)) {
		getCamera().moveRight(-3 * Core::GetSpeed());
	}

	if (Core::GetKeyboard().isKeyPressed(SDL_SCANCODE_W)) {
		getCamera().moveUp(3 * Core::GetSpeed());

	}
	else if (Core::GetKeyboard().isKeyPressed(SDL_SCANCODE_S)) {
		getCamera().moveUp(-3 * Core::GetSpeed());
	}

	if (Core::GetKeyboard().isKeyPressed(SDL_SCANCODE_R)) {
		getCamera().moveForward(9 * Core::GetSpeed());

	}
	else if (Core::GetKeyboard().isKeyPressed(SDL_SCANCODE_F)) {
		getCamera().moveForward(-9 * Core::GetSpeed());
	}

	if (Core::GetKeyboard().isKeyTriggered(SDL_SCANCODE_SPACE)) {
		player_pos++;
		drawOneFloor();
	}

}

void GameScene::drawOneFloor()
{
	using namespace Models;
	using namespace Graphics;
	if (drawed_roads < 3 && (drawed_roads == 0 || rand() % 2 == 0))
	{
		floors.push_back(std::make_shared<FloorColor>(progSimpleColor, 25.0f, 1.0f, 0.0f, 0.05 * (drawed_roads % 2) + 0.6, 0.05 * (drawed_roads % 2) + 0.6, 0.05 * (drawed_roads % 2) + 0.6));
		floors.back()->setPosition(0, 0, (floors.size() - 1)*(-2.0));
		add(floors.back());
		drawed_roads++;
	}
	else
	{
		floors.push_back(std::make_shared<FloorTexture>(progSimpleTexture, 25.0f, 1.0f, 0.0f, texFloor->getId()));
		floors.back()->setPosition(0, 0, (floors.size() - 1)*(-2.0));
		add(floors.back());
		drawed_roads = 0;
	}
}

void GameScene::resume() {
	Scene::resume();
}

void GameScene::pause() {
	Scene::pause();
}

void GameScene::hide() {
	Scene::hide();

	Core::GetShaderManager().deleteProgram("simple_texture");
	Core::GetShaderManager().deleteProgram("simple_color");
}