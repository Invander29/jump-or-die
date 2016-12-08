#include "GameScene.h"

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm> 

#include "Engine/Application.h"
#include "Engine/Models/FloorColor.h"
#include "Engine/Models/FloorTexture.h"
#include "Car.h"
#include "Tree.h"
#include "Engine/Utils/Message.h"

#include "Images/Images.h"

using namespace Scenes;
using namespace Utils;
using namespace Models;
using namespace Graphics;

extern Image ImageFloor;

GameScene::GameScene()
{
	// Shaders init
	mProgramTexture = Application::instance().shaderManager().get("simple_texture", ":simple_texture", ":simple_texture");
	mProgramColor = Application::instance().shaderManager().get("simple_color", ":simple_color", ":simple_color");
	mTextureFloor = Application::instance().resourceManager().texture("floor", &ImageFloor);

	// Some default settings
	Application::instance().setLightingMode(Lighting::Type::PHONG);
	Application::instance().enableMultisampling(true);
}

GameScene::~GameScene()
{
	if (mProgramTexture) {
		Application::instance().shaderManager().remove(mProgramTexture->name());
	}

	if (mProgramColor) {
		Application::instance().shaderManager().remove(mProgramColor->name());
	}

	if (mTextureFloor) {
		Application::instance().resourceManager().deleteTexture(mTextureFloor->name());
	}
}

void GameScene::show() 
{
	Scene::show();
	
	cameraPos = 0.0; //pocitadlo na poziciu kamery
	stopped = false;
	gameover = false;
	started = false;
	diffStep = 0.1f; //sluzi na zvacsovanie rychlosti pohybu kamery a aut, co zvysuje narocnost
	mDrawedRoads = 0;

	// Set light
	mLight.setPosition(0.0f, 10.0f, 0.0f);
	mLight.setColor(1, 1, 1);

	// Add camera object
	Camera camera(45.0f, 0.1f, 100.0f);
	camera.setPosition(3.0f, 25.0f, 3.0f);
	camera.lookUp(-55.0f);
	camera.lookRight(-7.0f);
	setCamera(camera);

	// Test trees
	// TODO Just a tree test (modify / remove)
	for (int i=0; i<20; ++i) {
		for (int a = 0; a < 2; ++a) {
			spTree tree = SMART(Tree, mProgramTexture);
			tree->setPosition((a*2 - 1) *  15.0f, 0, -i*2.0f);
			add(tree);
		}
	}

	// Player
	mPlayer = std::make_shared<Player>(mProgramTexture);
	mPlayer->setPosition(0, 0, -12);
	add(mPlayer);

	// Texts
	startGame = SMART(TextStart, mProgramColor);
	startGame->setPosition(0, 5, cameraPos*(-RATIO) - 13.0f);
	add(startGame);

	gameOver = SMART(TextGameOver, mProgramColor);
	pressSpace = SMART(TextPressSpace, mProgramColor);

	//Generate map
	spFloorTexture floor = std::make_shared<FloorTexture>(mProgramTexture, 25.0f, 1.0f, 0.0f, mTextureFloor->id());
	mFloors.push_back(floor);
	floor->setPosition(0.0, 0.0, (mFloors.size() - 1)*(-RATIO));
	add(floor);
	for (int i = 0; i < 3; i++)
	{
		spFloorColor floor2 = std::make_shared<FloorColor>(mProgramColor, 25.0f, 1.0f, 0.0f, 0.6f, 0.6f, 0.6f);
		mFloors.push_back(floor2);
		floor2->setPosition(0, 0.0, (mFloors.size() - 1)*(-RATIO));
		add(floor2);

		bool carsDirection = rand() % 2 != 0;
		float carsSpeed = ((float)rand() / (RAND_MAX / 10)) + 1.0f;
		int count = rand() % 3 + 2;
		std::vector<int> positions;
		for (int i = -24; i<24; i += 4) positions.push_back(i);
		std::random_shuffle(positions.begin(), positions.end());
		for (int i = 0; i < count; i++) //generovani aut na danej ceste
		{
			spCar car = std::make_shared<Car>(mProgramTexture, carsDirection, 0.0f, 0.0f, carsSpeed);
			mCars.push_back(car); //pridanie auta do zoznamu aut
			car->setPosition((float)positions[i], -0.3f, (mFloors.size() - 1)*(-RATIO) + 0.35f);
			add(car);
		}

		spFloorTexture floor3 = std::make_shared<FloorTexture>(mProgramTexture, 25.0f, 1.0f, 0.0f, mTextureFloor->id());
		mFloors.push_back(floor3);
		floor3->setPosition(0.0f, 0.0f, (mFloors.size() - 1)*(-RATIO));
		add(floor3);
	}
	
	srand(int(time(NULL)));
	for (int i = 0; i < FLOORS_COUNT - 3; i++)
	{
		drawOneFloor();
	}
}

void GameScene::update() 
{
	Scene::update();
	float moveLen;

	Application& app = Application::instance();

	// If game over, clear scene (hide) and show it again
	if (gameover && app.keyboard().isKeyTriggered(GLFW_KEY_SPACE)) {
		hide();
		show();
		return;
	}

	if (!started && app.keyboard().isKeyTriggered(GLFW_KEY_SPACE)) {
		startGame->setVisibility(false);
		started = true;
	}
			
	// Check if player has moved
	static int lastPlayerPosition = 0;
	if (lastPlayerPosition != mPlayer->jumpPosition()) {
		lastPlayerPosition = mPlayer->jumpPosition();
		drawOneFloor();
	}

	if (!stopped && started) //pohyb kamery
	{
		if (lastPlayerPosition - cameraPos > 0) {
			moveLen = (lastPlayerPosition - cameraPos + SPEED_CONS + diffStep / 3) * app.speed(); //zrychlenie ak je hrac velmi vpredu
		}
		else {
			moveLen = (SPEED_CONS + diffStep / 3) * app.speed();
		}

		camera().moveForward(moveLen*RATIO); //posun kamery *2 kvoli tomu ze sirka pasu je 2 nie 1
		mLight.setPosition(mLight.position()[0], mLight.position()[1], mLight.position()[2] - (moveLen*RATIO));
		cameraPos += moveLen;
	}

	if (!gameover)
	{
		for (auto const& car : mCars)
		{
			if (round(car->z() - 0.35) == round(mPlayer->z()) && fabs(car->x())<1.8f)
			{

				Message::debug("GAME OVER"); //TODO konec hry
				mPlayer->gameover();
				gameOver->setPosition(0, 5, cameraPos*(-RATIO) - 13.0f);
				add(gameOver);
				gameover = true;
				stopped = true;
				for (auto const& carstop : mCars)
				{
					carstop->gameover();
				}
				gameOver->setPosition(0, 5, cameraPos*(-RATIO) - 13.0f);
				add(gameOver);
			}
		}

		if (cameraPos - lastPlayerPosition > 7)
		{
			Message::debug("GAME OVER"); //TODO konec hry
			mPlayer->gameover();
			gameOver->setPosition(0, 5, cameraPos*(-RATIO) - 13.0f);
			add(gameOver);
			gameover = true;
			stopped = true;
			for (auto const& carstop : mCars)
			{
				carstop->gameover();
			}
		}
	}	
}

void GameScene::drawOneFloor()
{
	using namespace Models;
	using namespace Graphics;
	if (mDrawedRoads < 3 && (mDrawedRoads == 0 || rand() % 2 == 0))
	{
		spFloorColor floor = std::make_shared<FloorColor>(mProgramColor, 25.0f, 1.0f, 0.0f, 0.05f * (mDrawedRoads % 2) + 0.6f, 0.05f * (mDrawedRoads % 2) + 0.6f, 0.05f * (mDrawedRoads % 2) + 0.6f);
		mFloors.push_back(floor);
		floor->setPosition(0, 0, (mFloors.size() - 1)*(-RATIO));
		add(floor);

		mDrawedRoads++;
		bool carsDirection = rand() % 2 != 0;
		float carsSpeed = ((float)rand() / (RAND_MAX / 10)) + 1.0f + diffStep;
		int count = rand() % 3 + 2;
		std::vector<int> positions;
		for (int i = -24; i<24; i += 4) positions.push_back(i);
		std::random_shuffle(positions.begin(), positions.end());
		for (int i = 0; i < count; i++) //generovani aut na danej ceste
		{
			spCar car = std::make_shared<Car>(mProgramTexture, carsDirection, 0.0f, 0.0f, carsSpeed);
			mCars.push_back(car); //pridanie auta do zoznamu aut
			car->setPosition((float)positions[i], -0.3f, (mFloors.size() - 1)*(-RATIO) + 0.35f);
			add(car);
		}
	}
	else
	{
		spFloorTexture floor = std::make_shared<FloorTexture>(mProgramTexture, 25.0f, 1.0f, 0.0f, mTextureFloor->id());
		mFloors.push_back(floor);
		floor->setPosition(0, 0, (mFloors.size() - 1)*(-RATIO));
		add(floor);
		mDrawedRoads = 0;
	}
	diffStep += 0.1f;
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

	// Clear scene objects
	mFloors.clear();
	mCars.clear();
	mPlayer = nullptr;
	gameOver = nullptr;
	startGame = nullptr;
}