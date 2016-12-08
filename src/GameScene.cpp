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

/**
* Konstruktor hernej sceny, sluzi na nacitanie shaderov, zakladne nastavenia a pod.
*
* \brief Konstruktor hernej sceny
* \author Pavel Reznak
*/
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

/**
* Destruktor hernej sceny, sluzi na odstranenie shaderov a pod.
*
* \brief Destruktor hernej sceny
* \author Pavel Reznak
*/
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

/**
* Tato metoda sluzi na vykreslenie sceny na zaciatku.
*
* \brief Prvotne vykreslenie sceny
* \author Pavel Reznak
* \author Martin Tomovic
*/
void GameScene::show()
{
	Scene::show();

	cameraPos = 0.0; //pocitadlo na poziciu kamery
	stopped = false; //identifikacie ci je pozastaveny pohyb kamery
	gameover = false; //identifikacia prehry
	started = false; //identifikacia ci uz hrac zacal hrat
	mDiff = 0.1f; //sluzi na zvacsovanie rychlosti pohybu kamery a aut, co zvysuje narocnost
	mDrawedRoads = 0; //pocitadlo vykreslenych pasov cesty od posledneho pasu travy

	// Set light
	mLight.setPosition(0.0f, 10.0f, 0.0f);
	mLight.setColor(1, 1, 1);

	// Add camera object
	Camera camera(45.0f, 0.1f, 100.0f);
	camera.setPosition(3.0f, 25.0f, 3.0f);
	camera.lookUp(-55.0f);
	camera.lookRight(-7.0f);
	setCamera(camera);

	// Player
	mPlayer = std::make_shared<Player>(mProgramTexture);
	mPlayer->setPosition(0, 0, -12);
	add(mPlayer);

	// Texts
	//text Start, ten mozme hned na zaciatku zobrazit pomocou add
	startGame = SMART(TextStart, mProgramColor);
	startGame->setPosition(0, 5, cameraPos*(-RATIO) - 12.0f);
	add(startGame);
	//texty pri prehre, predpripravime si ich aby sa nacitali ich textury a vykreslime ich az pri prehre
	pressSpace = SMART(TextPressSpace, mProgramColor);
	gameOver = SMART(TextGameOver, mProgramColor);

	//Generate map
	//generovanie prveho travoveho pasu
	spFloorTexture floor = std::make_shared<FloorTexture>(mProgramTexture, 25.0f, 1.0f, 0.0f, mTextureFloor->id());
	mFloors.push_back(floor);
	floor->setPosition(0.0, 0.0, (mFloors.size() - 1)*(-RATIO));
	add(floor);
	int count = rand() % 9;
	std::vector<int> treepositions;
	for (int i = -24; i <= -4; i += 2) treepositions.push_back(i);
	for (int i = 4; i <= 24; i += 2) treepositions.push_back(i);
	std::random_shuffle(treepositions.begin(), treepositions.end());
	for (int i = 0; i < count; i++) //generovani stromov na trave
	{
		spTree tree = SMART(Tree, mProgramTexture);
		tree->setPosition(treepositions[i], 0, (mFloors.size() - 1)*(-RATIO));
		add(tree);
	}
	//generovanie dalsich pasov az po poziciu hraca na zaciatku
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
		count = rand() % 9;
		std::random_shuffle(treepositions.begin(), treepositions.end());
		for (int i = 0; i < count; i++) //generovani stromov na trave
		{
			spTree tree = SMART(Tree, mProgramTexture);
			tree->setPosition(treepositions[i], 0, (mFloors.size() - 1)*(-RATIO));
			add(tree);
		}
	}

	//inicializacia (seed) pre funkciu rand() pomocou aktualneho casu
	srand(int(time(NULL)));

	//nahodne generovani dalsich pasov, to uz je nahodne, generuje sa po vzdialenost FLOORS_COUNT, tak aby pohlad kamery bol vzdy zaplneny pasmi
	for (int i = 0; i < FLOORS_COUNT - 3; i++)
	{
		drawOneFloor();
	}
}

/**
* Tato metoda sluzi na prekreslovanie sceny pri kazdej iteracii.
*
* \brief Prekreslovanie sceny
* \author Pavel Reznak
* \author Martin Tomovic
*/
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

	//ak hra este len zacala a uzivatel stlaci prvy krat medzernik skryjeme text Start
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

	//automaticky pohyb kamery
	if (!stopped && started)
	{
		if (lastPlayerPosition - cameraPos > 0) {
			moveLen = (lastPlayerPosition - cameraPos + SPEED_CONS + mDiff / 3) * app.speed(); //zrychlenie ak je hrac velmi vpredu
		}
		else {
			moveLen = (SPEED_CONS + mDiff / 3) * app.speed();
		}

		camera().moveForward(moveLen*RATIO); //posun kamery
		mLight.setPosition(mLight.position()[0], mLight.position()[1], mLight.position()[2] - (moveLen*RATIO));
		cameraPos += moveLen;
	}

	//detekcia prehry
	if (!gameover)
	{
		//detekcia kolizie s niektorym z aut
		for (auto const& car : mCars)
		{
			if (round(car->z() - 0.35) == round(mPlayer->z()) && fabs(car->x())<1.8f)
			{

				Message::debug("GAME OVER");
				mPlayer->gameover();
				//vypis textov informujucich o prehre a dalsom postupe
				gameOver->setPosition(0, 5, cameraPos*(-RATIO) - 13.0f);
				add(gameOver);
				pressSpace->setPosition(0, 5, cameraPos*(-RATIO) - 8.0f);
				add(pressSpace);
				gameover = true;
				stopped = true;
				//tymto posleme spravu autickam ze sa maju zastavit
				for (auto const& carstop : mCars)
				{
					carstop->gameover();
				}
			}
		}

		//detekcia prehry, ktora nastane ak hrac nestiha kamere
		if (cameraPos - lastPlayerPosition > 7)
		{
			Message::debug("GAME OVER");
			mPlayer->gameover();
			//vypis textov informujucich o prehre a dalsom postupe
			gameOver->setPosition(0, 5, cameraPos*(-RATIO) - 13.0f);
			add(gameOver);
			pressSpace->setPosition(0, 5, cameraPos*(-RATIO) - 8.0f);
			add(pressSpace);
			gameover = true;
			stopped = true;
			//tymto posleme spravu autickam ze sa maju zastavit
			for (auto const& carstop : mCars)
			{
				carstop->gameover();
			}
		}
	}
}

/**
* Tato metoda sluzi na pridanie dalsieho pasu cesty alebo travy a vytvorenie objektov na nich naviazanych.
*
* \brief Vykreslenie dalsieho pasu
* \author Martin Tomovic
*/
void GameScene::drawOneFloor()
{
	using namespace Models;
	using namespace Graphics;
	//rozhodnutie ci sa vykresli cesta alebo trava, maximalny pocet pruhov cesty je 3, no ak ich je zatial menej je nahodne ci sa vykresli cesta alebo trava
	if (mDrawedRoads < 3 && (mDrawedRoads == 0 || rand() % 2 == 0))
	{
		//vykreslenie cesty a pridanie do zoznamu pasov a do sceny
		spFloorColor floor = std::make_shared<FloorColor>(mProgramColor, 25.0f, 1.0f, 0.0f, 0.05f * (mDrawedRoads % 2) + 0.6f, 0.05f * (mDrawedRoads % 2) + 0.6f, 0.05f * (mDrawedRoads % 2) + 0.6f);
		mFloors.push_back(floor);
		floor->setPosition(0, 0, (mFloors.size() - 1)*(-RATIO));
		add(floor);

		mDrawedRoads++;
		//nahodne urcime smer pohybu auta, rychlost auta a pocet aut v pase cesty, hodnoty boli optimalizovane na dobru hratelnost 
		bool carsDirection = rand() % 2 != 0;
		float carsSpeed = ((float)rand() / (RAND_MAX / 10)) + 1.0f + mDiff;
		int count = rand() % 3 + 2;
		//vyvorime zoznam moznych zaciatocnych pozicii aut
		std::vector<int> positions;
		for (int i = -24; i<24; i += 4) positions.push_back(i);
		//nahodne premiesanie zoznamu aby boli auticka nahodne rozmiestnene
		std::random_shuffle(positions.begin(), positions.end());
		//generovani aut na danej ceste podla nahodne urceneho poctu
		for (int i = 0; i < count; i++)
		{
			spCar car = std::make_shared<Car>(mProgramTexture, carsDirection, 0.0f, 0.0f, carsSpeed);
			mCars.push_back(car); //pridanie auta do zoznamu aut
			car->setPosition((float)positions[i], -0.3f, (mFloors.size() - 1)*(-RATIO) + 0.35f);
			add(car);
		}
	}
	else
	{
		//vykreslenie travy a pridanie do zoznamu pasov s do sceny
		spFloorTexture floor = std::make_shared<FloorTexture>(mProgramTexture, 25.0f, 1.0f, 0.0f, mTextureFloor->id());
		mFloors.push_back(floor);
		floor->setPosition(0, 0, (mFloors.size() - 1)*(-RATIO));
		add(floor);
		//vynulovanie pocitadla posty vykreslenych ciest od pasu travy 
		mDrawedRoads = 0;
		int count = rand() % 9;
		//vytvorime zoznam moznych pozicii stromov, nemozu to byt napr. pozicie moc v blizkosti pohybu hraca
		std::vector<int> treepositions;
		for (int i = -24; i <= -4; i += 2) treepositions.push_back(i);
		for (int i = 4; i <= 24; i += 2) treepositions.push_back(i);
		std::random_shuffle(treepositions.begin(), treepositions.end());
		for (int i = 0; i < count; i++) //generovani stromov na trave
		{
			spTree tree = SMART(Tree, mProgramTexture);
			tree->setPosition(treepositions[i], 0, (mFloors.size() - 1)*(-RATIO));
			add(tree);
		}
	}
	//zvysenie obtiaznosti hry
	mDiff += DIFF_STEP;
}

/**
* Tato metoda sluzi na obnovenie sceny po zastaveni.
*
* \brief Obnovenie pozastavenej hernej sceny
* \author Pavel Reznak
*/
void GameScene::resume()
{
	Scene::resume();
}

/**
* Tato metoda sluzi na pozastavenie sceny.
*
* \brief Pozastavenie hernej sceny
* \author Pavel Reznak
*/
void GameScene::pause()
{
	Scene::pause();
}

/**
* Tato metoda sluzi na zrusenie nastaveni sceny.
*
* \brief Zrusenie hernej sceny
* \author Pavel Reznak
*/
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