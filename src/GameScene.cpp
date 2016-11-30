#include <cstdlib>
#include <ctime>
#include "GameScene.h"
#include "Engine/Models/CubeTexture.h"
#include "Engine/Application.h"
#include "Engine/Models/Floor.h"
#include "Engine/Models/CubeColor.h"
#include "Engine/Models/FloorColor.h"
#include "Engine/Models/FloorTexture.h"
#include "Engine/Models/Triangle.h"
#include "Car.h"
#include "TraficSign.h"
#include "Tree.h"


using namespace Scenes;

GameScene::GameScene()
{
}


GameScene::~GameScene()
{
	Application::instance().shaderManager().remove(mProgramTexture);
	Application::instance().shaderManager().remove(mProgramColor);

	Application::instance().resourceManager().deleteTexture(mTextureCube->name());
	Application::instance().resourceManager().deleteTexture(mTextureFloor->name());
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

	// Shaders init
	mProgramTexture = Application::instance().shaderManager().get("simple_color", "simple_texture.vs", "simple_texture.fs");
	mProgramColor = Application::instance().shaderManager().get("simple_texture", "simple_color.vs", "simple_color.fs");
	mTextureCube = Application::instance().resourceManager().texture("cube.png");
	mTextureFloor = Application::instance().resourceManager().texture("floor.png");

	// Objects TODO! this is just example
	// Create some cars
	for (int i = 0; i < 10; ++i) {
		spCar car = SMART(Car, mProgramColor.id, (i % 2) ? true : false, i / 4.0f, 3.0f, 5.0f);
		car->setZ(-i * 2);
		add(car);
	}

	// Create some trafic signs (only for effect)
	// TODO this is just example
	for (int i = 0; i < 10; ++i) {
		spTraficSign sign = SMART(TraficSign, mProgramColor.id);
		sign->setZ(-i * 2);
		sign->setX(-10 + i * 2);
		add(sign);
	}

	// Create some trees (only for effect)
	// TODO this is just example
	for (int i = 0; i < 10; ++i) {
		spTree tree = SMART(Tree, mProgramColor.id);
		tree->setZ(-i * 2);
		tree->setX(10 - i * 2);
		add(tree);
	}

	// Player
	mPlayer = std::make_shared<Player>(mProgramColor.id);
	mPlayer->setPosition(0, 0, -4);
	add(mPlayer);

	//Generate map
	mFloors.push_back(std::make_shared<FloorTexture>(mProgramTexture.id, 25.0f, 1.0f, 0.0f, mTextureFloor->id()));
	mFloors.back()->setPosition(0, 0, (mFloors.size() - 1)*(-2.0));
	add(mFloors.back());
	mFloors.push_back(std::make_shared<FloorColor>(mProgramColor.id, 25.0f, 1.0f, 0.0f, 0.6f, 0.6f, 0.6f));
	mFloors.back()->setPosition(0, 0, (mFloors.size() - 1)*(-2.0));
	add(mFloors.back());
	mFloors.push_back(std::make_shared<FloorTexture>(mProgramTexture.id, 25.0f, 1.0f, 0.0f, mTextureFloor->id()));
	mFloors.back()->setPosition(0, 0, (mFloors.size() - 1)*(-2.0));
	add(mFloors.back());
	mDrawedRoads = 0;
	srand(int(time(NULL)));
	for (int i = 0; i < FLOORS_COUNT-3; i++)
	{
		drawOneFloor();
	}
}

void GameScene::update() {
	Scene::update();

	Application& app = Application::instance();
	if (app.keyboard().isKeyPressed(GLFW_KEY_J)) {
		camera().lookRight(-3 * app.speed());

	}
	else if (app.keyboard().isKeyPressed(GLFW_KEY_L)) {
		camera().lookRight(3 * app.speed());
	}

	if (app.keyboard().isKeyPressed(GLFW_KEY_I)) {
		camera().lookUp(3 * app.speed());

	}
	else if (app.keyboard().isKeyPressed(GLFW_KEY_K)) {
		camera().lookUp(-3 * app.speed());
	}

	if (app.keyboard().isKeyPressed(GLFW_KEY_O)) {
		camera().lookSide(3 * app.speed());

	}
	else if (app.keyboard().isKeyPressed(GLFW_KEY_P)) {
		camera().lookSide(-3 * app.speed());
	}

	if (app.keyboard().isKeyPressed(GLFW_KEY_A)) {
		camera().moveRight(3 * app.speed());

	}
	else if (app.keyboard().isKeyPressed(GLFW_KEY_D)) {
		camera().moveRight(-3 * app.speed());
	}

	if (app.keyboard().isKeyPressed(GLFW_KEY_W)) {
		camera().moveUp(3 * app.speed());

	}
	else if (app.keyboard().isKeyPressed(GLFW_KEY_S)) {
		camera().moveUp(-3 * app.speed());
	}

	if (app.keyboard().isKeyPressed(GLFW_KEY_R)) {
		camera().moveForward(9 * app.speed());

	}
	else if (app.keyboard().isKeyPressed(GLFW_KEY_F)) {
		camera().moveForward(-9 * app.speed());
	}

	// Check if player has moved
	static int lastPlayerPosition = 0;
	if (lastPlayerPosition != mPlayer->jumpPosition()) {
		lastPlayerPosition = mPlayer->jumpPosition();
		drawOneFloor();
	}
}

void GameScene::drawOneFloor()
{
	using namespace Models;
	using namespace Graphics;
	if (mDrawedRoads < 3 && (mDrawedRoads == 0 || rand() % 2 == 0))
	{
		mFloors.push_back(std::make_shared<FloorColor>(mProgramColor.id, 25.0f, 1.0f, 0.0f, 0.05 * (mDrawedRoads % 2) + 0.6, 0.05 * (mDrawedRoads % 2) + 0.6, 0.05 * (mDrawedRoads % 2) + 0.6));
		mFloors.back()->setPosition(0, 0, (mFloors.size() - 1)*(-2.0));
		add(mFloors.back());
		mDrawedRoads++;
	}
	else
	{
		mFloors.push_back(std::make_shared<FloorTexture>(mProgramTexture.id, 25.0f, 1.0f, 0.0f, mTextureFloor->id()));
		mFloors.back()->setPosition(0, 0, (mFloors.size() - 1)*(-2.0));
		add(mFloors.back());
		mDrawedRoads = 0;
	}
}

void GameScene::resume() 
{
	Scene::resume();
}

void GameScene::pause() 
{
	Scene::pause();
}

void GameScene::hide() 
{
	Scene::hide();
}