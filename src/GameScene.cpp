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
#include "Tree.h"
#include "Engine/Utils/Message.h"


using namespace Scenes;
using namespace Utils;

GameScene::GameScene()
{
}


GameScene::~GameScene()
{
	if (mProgramTexture) {
		Application::instance().shaderManager().remove(mProgramTexture->name());
	}

	if (mProgramColor) {
		Application::instance().shaderManager().remove(mProgramColor->name());
	}

	if (mTextureCube) {
		Application::instance().resourceManager().deleteTexture(mTextureCube->name());
	}

	if (mTextureFloor) {
		Application::instance().resourceManager().deleteTexture(mTextureFloor->name());
	}
}

void GameScene::show() {
	Scene::show();
	// Set light
	mLight.setPosition(0.0f, 10.0f, 0.0f);
	mLight.setColor(1, 1, 1);
	Application::instance().setLightingMode(Lighting::Type::PHONG);

	// Add camera object
	Camera camera(45.0f, 0.1f, 100.0f);
	/*camera.lookAt(glm::vec3(2.0f, 25.0f, 3.0f),  // Camera is in this position
		glm::vec3(0.0f, 0.0f, -12.0f));// Camera looks at this position)*/
	camera.setPosition(3.0f, 25.0f, 3.0f);
	camera.lookUp(-55.0f);
	camera.lookRight(-7.0f);
	setCamera(camera);
	cameraPos = 0.0; //pocitadlo na poziciu kamery
	stopped = false;
	gameover = false;
	started = false;
	diffStep = 0.1f; //sluzi na zvacsovanie rychlosti pohybu kamery a aut, co zvysuje narocnost

	// Add objects to scene
	using namespace Models;
	using namespace Graphics;

	// Shaders init
	mProgramTexture = Application::instance().shaderManager().get("simple_texture", "simple_texture", "simple_texture");
	mProgramColor = Application::instance().shaderManager().get("simple_color", "simple_color", "simple_color");
	mTextureCube = Application::instance().resourceManager().texture("cube.png");
	mTextureFloor = Application::instance().resourceManager().texture("floor.png");
	

	// Test trees
	// TODO Just a tree test (modify / remove)
	for (int i=0; i<20; ++i) {
		for (int a = 0; a < 2; ++a) {
			spTree tree = SMART(Tree, mProgramTexture);
			tree->setPosition((a*2 - 1) *  15, 0, -i*2);
			add(tree);
		}
	}

	// Test of texts

	// Player
	mPlayer = std::make_shared<Player>(mProgramTexture);
	mPlayer->setPosition(0, 0, -12);
	add(mPlayer);

	// Texts
	startGame = SMART(TextStart, mProgramTexture);
	startGame->setPosition(0, 5, cameraPos*(-RATIO) - 13.0);
	add(startGame);

	gameOver = SMART(TextGameOver, mProgramTexture);

	//Generate map
	mFloors.push_back(std::make_shared<FloorTexture>(mProgramTexture, 25.0f, 1.0f, 0.0f, mTextureFloor->id()));
	mFloors.back()->setPosition(0.0, 0.0, (mFloors.size() - 1)*(-RATIO));
	add(mFloors.back());
	for (int i = 0; i < 3; i++)
	{
		mFloors.push_back(std::make_shared<FloorColor>(mProgramColor, 25.0f, 1.0f, 0.0f, 0.6f, 0.6f, 0.6f));
		mFloors.back()->setPosition(0, 0.0, (mFloors.size() - 1)*(-RATIO));
		add(mFloors.back());
		bool carsDirection = rand() % 2;
		float carsSpeed = ((float)rand() / (RAND_MAX / 10)) + 1.0f;
		int count = rand() % 3 + 2;
		std::vector<int> positions;
		for (int i = -24; i<24; i += 4) positions.push_back(i);
		std::random_shuffle(positions.begin(), positions.end());
		for (int i = 0; i < count; i++) //generovani aut na danej ceste
		{
			mCars.push_back(std::make_shared<Car>(mProgramTexture, carsDirection, 0.0f, 0.0f, carsSpeed)); //pridanie auta do zoznamu aut
			mCars.back()->setPosition((float)positions[i], -0.3, (mFloors.size() - 1)*(-RATIO) + 0.35);
			add(mCars.back());
		}
		mFloors.push_back(std::make_shared<FloorTexture>(mProgramTexture, 25.0f, 1.0f, 0.0f, mTextureFloor->id()));
		mFloors.back()->setPosition(0.0, 0.0, (mFloors.size() - 1)*(-RATIO));
		add(mFloors.back());
	}
	mDrawedRoads = 0;
	srand(int(time(NULL)));
	for (int i = 0; i < FLOORS_COUNT - 3; i++)
	{
		drawOneFloor();
	}
}

void GameScene::update() {
	Scene::update();
	float moveLen;

	Application& app = Application::instance();
	float cameraSpeed = 45.0f;

	if (app.keyboard().isKeyPressed(GLFW_KEY_J)) {
		camera().lookRight(-cameraSpeed * app.speed());

	}
	else if (app.keyboard().isKeyPressed(GLFW_KEY_L)) {
		camera().lookRight(cameraSpeed * app.speed());
	}

	if (app.keyboard().isKeyPressed(GLFW_KEY_I)) {
		camera().lookUp(cameraSpeed * app.speed());

	}
	else if (app.keyboard().isKeyPressed(GLFW_KEY_K)) {
		camera().lookUp(-cameraSpeed * app.speed());
	}

	if (app.keyboard().isKeyPressed(GLFW_KEY_O)) {
		camera().lookSide(cameraSpeed * app.speed());

	}
	else if (app.keyboard().isKeyPressed(GLFW_KEY_P)) {
		camera().lookSide(-cameraSpeed * app.speed());
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
		mLight.setPosition(mLight.position()[0], mLight.position()[1], mLight.position()[2] - (moveLen*2.0));
		cameraPos += moveLen;
	}
	else if (app.keyboard().isKeyPressed(GLFW_KEY_F)) {
		moveLen = -5 * app.speed();
		camera().moveForward(moveLen*2.0);
		mLight.setPosition(mLight.position()[0], mLight.position()[1], mLight.position()[2] - (moveLen*2.0));
		cameraPos += moveLen;
	}

	if (app.keyboard().isKeyTriggered(GLFW_KEY_X)) {
		stopped=!stopped;
	}

	if (gameover && app.keyboard().isKeyTriggered(GLFW_KEY_SPACE)) {
		Scenes::spGameScene scene = std::make_shared<Scenes::GameScene>(); //TODO PAVEL
		Application::instance().sceneManager().set(scene);
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
				gameOver->setPosition(0, 5, cameraPos*(-RATIO) - 13.0);
				add(gameOver);
				gameover = true;
				stopped = true;
				for (auto const& carstop : mCars)
				{
					carstop->gameover();
				}
				gameOver->setPosition(0, 5, cameraPos*(-RATIO) - 13.0);
				add(gameOver);
			}
		}

		if (cameraPos - lastPlayerPosition > 7)
		{
			Message::debug("GAME OVER"); //TODO konec hry
			mPlayer->gameover();
			gameOver->setPosition(0, 5, cameraPos*(-RATIO) - 13.0);
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
		mFloors.push_back(std::make_shared<FloorColor>(mProgramColor, 25.0f, 1.0f, 0.0f, 0.05 * (mDrawedRoads % 2) + 0.6, 0.05 * (mDrawedRoads % 2) + 0.6, 0.05 * (mDrawedRoads % 2) + 0.6));
		mFloors.back()->setPosition(0, 0, (mFloors.size() - 1)*(-RATIO));
		add(mFloors.back());
		mDrawedRoads++;
		bool carsDirection = rand() % 2;
		float carsSpeed = ((float)rand() / (RAND_MAX / 10)) + 1.0f + diffStep;
		int count = rand() % 3 + 2;
		std::vector<int> positions;
		for (int i = -24; i<24; i += 4) positions.push_back(i);
		std::random_shuffle(positions.begin(), positions.end());
		for (int i = 0; i < count; i++) //generovani aut na danej ceste
		{
			mCars.push_back(std::make_shared<Car>(mProgramTexture, carsDirection, 0.0f, 0.0f, carsSpeed)); //pridanie auta do zoznamu aut
			mCars.back()->setPosition((float)positions[i], -0.3, (mFloors.size() - 1)*(-RATIO) + 0.35);
			add(mCars.back());
		}
	}
	else
	{
		mFloors.push_back(std::make_shared<FloorTexture>(mProgramTexture, 25.0f, 1.0f, 0.0f, mTextureFloor->id()));
		mFloors.back()->setPosition(0, 0, (mFloors.size() - 1)*(-RATIO));
		add(mFloors.back());
		mDrawedRoads = 0;
	}
	diffStep += 0.1;
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