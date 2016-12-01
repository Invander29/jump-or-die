#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm> 
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
#include "Engine/Utils/Message.h"


using namespace Scenes;
using namespace Utils;

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
	cameraPos = 0.0;
	stopped = false;
	gameover = false;

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
	/*for (int i = 0; i < 10; ++i) {
		spCar car = SMART(Car, mProgramColor.id, (i % 2) ? true : false, i / 4.0f, 3.0f, 3.0f);
		car->setZ(-i * 2);
		add(car);
	}*/

	// Create some trafic signs (only for effect)
	// TODO this is just example
	/*for (int i = 0; i < 10; ++i) {
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
	}*/

	// Player
	mPlayer = std::make_shared<Player>(mProgramColor.id);
	mPlayer->setPosition(0, 0, -12);
	add(mPlayer);

	//Generate map
	mFloors.push_back(std::make_shared<FloorTexture>(mProgramTexture.id, 25.0f, 1.0f, 0.0f, mTextureFloor->id()));
	mFloors.back()->setPosition(0, -1.0, (mFloors.size() - 1)*(-2.0));
	add(mFloors.back());
	for (int i = 0; i < 3; i++)
	{
		mFloors.push_back(std::make_shared<FloorColor>(mProgramColor.id, 25.0f, 1.0f, 0.0f, 0.6f, 0.6f, 0.6f));
		mFloors.back()->setPosition(0, -1.0, (mFloors.size() - 1)*(-2.0));
		add(mFloors.back());
		bool carsDirection = rand() % 2;
		float carsSpeed = ((float)rand() / (RAND_MAX / 10)) + 1.0f;
		int count = rand() % 4 + 3;
		std::vector<int> positions;
		for (int i = -25; i <= 25; i += 2) positions.push_back(i);
		std::random_shuffle(positions.begin(), positions.end());
		for (int i = 0; i < count; i++) //generovani aut na danej ceste
		{
			mCars.push_back(std::make_shared<Car>(mProgramColor.id, carsDirection, 0.0f, 0.0f, carsSpeed)); //pridanie auta do zoznamu aut
			mCars.back()->setX((float)positions[i]);
			mCars.back()->setZ((mFloors.size() - 1)*(-2.0));
			add(mCars.back());
		}
		mFloors.push_back(std::make_shared<FloorTexture>(mProgramTexture.id, 25.0f, 1.0f, 0.0f, mTextureFloor->id()));
		mFloors.back()->setPosition(0, -1.0, (mFloors.size() - 1)*(-2.0));
		add(mFloors.back());
	}
	mDrawedRoads = 0;
	srand(int(time(NULL)));
	for (int i = 0; i < FLOORS_COUNT-3; i++)
	{
		drawOneFloor();
	}
}

void GameScene::update() {
	Scene::update();
	float moveLen;

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
		moveLen = 5 * app.speed();
		camera().moveForward(moveLen*2.0);
		cameraPos += moveLen;
	}
	else if (app.keyboard().isKeyPressed(GLFW_KEY_F)) {
		moveLen = -5 * app.speed();
		camera().moveForward(moveLen*2.0);
		cameraPos += moveLen;
	}

	if (app.keyboard().isKeyTriggered(GLFW_KEY_X)) {
		stopped=!stopped;
	}
		
	// Check if player has moved
	static int lastPlayerPosition = 0;
	if (lastPlayerPosition != mPlayer->jumpPosition()) {
		lastPlayerPosition = mPlayer->jumpPosition();
		drawOneFloor();
	}

	if (!stopped) //pohyb kamery
	{
		if (lastPlayerPosition - cameraPos > 0) {
			moveLen = (lastPlayerPosition - cameraPos + SPEED_CONS) * app.speed(); //zrychlenie ak je hrac velmi vpredu
		}
		else {
			moveLen = SPEED_CONS * app.speed();
		}

		camera().moveForward(moveLen*2.0);
		cameraPos += moveLen;
	}

	if (!gameover)
	{
		for (auto const& car : mCars)
		{
			if (car->z() == round(mPlayer->z()) && fabs(car->x())<1.6f)
			{

				Message::debug("GAME OVER"); //TODO konec hry
				gameover = true;
				stopped = true;
			}
		}

		if (cameraPos - lastPlayerPosition > 7)
		{
			Message::debug("GAME OVER"); //TODO konec hry
			gameover = true;
			stopped = true;
		}
	}	
}

void GameScene::drawOneFloor()
{
	using namespace Models;
	using namespace Graphics;
	if (mDrawedRoads < 3 && (mDrawedRoads == 0 || rand() % 2 == 0))
	{
		mFloors.push_back(std::make_shared<FloorColor>(mProgramColor.id, 25.0f, 1.0f, 0.0f, 0.05 * (mDrawedRoads % 2) + 0.6, 0.05 * (mDrawedRoads % 2) + 0.6, 0.05 * (mDrawedRoads % 2) + 0.6));
		mFloors.back()->setPosition(0, -1.0, (mFloors.size() - 1)*(-2.0));
		add(mFloors.back());
		mDrawedRoads++;
		bool carsDirection = rand() % 2;
		float carsSpeed = ((float)rand() / (RAND_MAX / 10)) + 1.0f;
		int count = rand() % 4 + 3;
		std::vector<int> positions;
		for (int i = -25; i<=25; i+=2) positions.push_back(i);
		std::random_shuffle(positions.begin(), positions.end());
		for (int i=0; i < count; i++) //generovani aut na danej ceste
		{
			mCars.push_back(std::make_shared<Car>(mProgramColor.id, carsDirection, 0.0f, 0.0f, carsSpeed)); //pridanie auta do zoznamu aut
			mCars.back()->setX((float)positions[i]);
			mCars.back()->setZ((mFloors.size() - 1)*(-2.0));
			add(mCars.back());
		}
	}
	else
	{
		mFloors.push_back(std::make_shared<FloorTexture>(mProgramTexture.id, 25.0f, 1.0f, 0.0f, mTextureFloor->id()));
		mFloors.back()->setPosition(0, -1.0, (mFloors.size() - 1)*(-2.0));
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