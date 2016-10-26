#include "GameScene.h"
#include "Engine/Models/CubeTexture.h"
#include "Engine/Core.h"
#include "Engine/Models/Floor.h"
#include "Engine/Models/CubeColor.h"
#include "Engine/Models/FloorColor.h"
#include "Engine/Models/FloorTexture.h"

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
	camera.lookAt(glm::vec3(0.0f, 2.0f, 0.0f),  // Camera is in this position
	              glm::vec3(0.0f, 0.0f, -4.0f));// Camera looks at this position)
	setCamera(camera);

	// Add objects to scene
	using namespace Models;
	using namespace Graphics;

	// Shaders for texture
	GLuint progSimpleTexture = Core::GetShaderManager().createProgram("simple_texture", "simple_texture.vs", "simple_texture.fs");
	spTexture texCube = Core::GetResourceManager().getTexture("cube.png");

	// Cube with texture on position 0 0 -4
	spCube cube = std::make_shared<CubeTexture>(progSimpleTexture, 1.0f, texCube->getId());
	cube->setPosition(0, 1, -4);
	add(cube);

	// Shaders for single color
	GLuint progSimpleColor = Core::GetShaderManager().createProgram("simple_color", "simple_color.vs", "simple_color.fs");

	// Floor with single color
	spFloor floorColor = std::make_shared<FloorColor>(progSimpleColor, 3.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	floorColor->setPosition(0, 0, -4);
	add(floorColor);

	// Floor with texture
	spTexture texFloor = Core::GetResourceManager().getTexture("floor.png");
	texFloor->setWrapping(GL_REPEAT, GL_REPEAT);
	spFloor floorTexture = std::make_shared<FloorTexture>(progSimpleTexture, 3.0f, 1.0f, 0.0f, texFloor->getId());
	floorTexture->setPosition(0, -1, -4);
	add(floorTexture);

	// Cube with single color
	//add(std::make_shared<CubeColor>(progSimpleColor, 1.0f, 0.0f, 0.0f, 1.0f));
}

void GameScene::update() {
	Scene::update();

	if (Core::GetKeyboard().isKeyPressed(SDL_SCANCODE_O)) {
		getCamera().lookRight(-3 * Core::GetSpeed());

	} else if (Core::GetKeyboard().isKeyPressed(SDL_SCANCODE_P)) {
		getCamera().lookRight( 3 * Core::GetSpeed());
	}

	if (Core::GetKeyboard().isKeyPressed(SDL_SCANCODE_I)) {
		getCamera().lookUp( 3 * Core::GetSpeed());

	} else if (Core::GetKeyboard().isKeyPressed(SDL_SCANCODE_K)) {
		getCamera().lookUp(-3 * Core::GetSpeed());
	}

	if (Core::GetKeyboard().isKeyPressed(SDL_SCANCODE_U)) {
		getCamera().lookSide(3 * Core::GetSpeed());

	} else if (Core::GetKeyboard().isKeyPressed(SDL_SCANCODE_Y)) {
		getCamera().lookSide(-3 * Core::GetSpeed());
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
