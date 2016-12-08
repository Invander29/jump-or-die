#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Engine/Scenes/Scene.h"
#include "Engine/Models/Floor.h"
#include "Player.h"
#include "Engine/Application.h"
#include "Car.h"
#include "TextGameOver.h"
#include "TextStart.h"
#include "TextPressSpace.h"

namespace Scenes {

	class GameScene : public Scene {
	public:

		/**
		* Konstruktor hernej sceny, sluzi na nacitanie shaderov, zakladne nastavenia a pod.
		*/
		explicit GameScene();

		/**
		* Destruktor hernej sceny, sluzi na odstranenie shaderov a pod.
		*/
		virtual ~GameScene();

		/**
		* Tato metoda sluzi na vykreslenie sceny na zaciatku.
		*/
		void show() override;
		
		/**
		* Tato metoda sluzi na obnovenie sceny po zastaveni.
		*/
		void resume() override;
		
		/**
		* Tato metoda sluzi na pozastavenie sceny.
		*/
		void pause() override;
		
		/**
		* Tato metoda sluzi na zrusenie nastaveni sceny.
		*/
		void hide() override;
		
		/**
		* Tato metoda sluzi na prekreslovanie sceny pri kazdej iteracii.
		*/
		void update() override;

	private:
		
		/**
		* Tato metoda sluzi na pridanie dalsieho pasu cesty alebo travy a vytvorenie objektov na nich naviazanych.
		*/
		void drawOneFloor();

		std::vector<Models::spFloor> mFloors;
		std::vector<spCar> mCars;
		spPlayer mPlayer;
		spTextGameOver gameOver;
		spTextStart startGame;
		spTextPressSpace pressSpace;

		static const int FLOORS_COUNT = 24;
		const float SPEED_CONS = 1.0;
		const float RATIO = 2.0;
		const float DIFF_STEP = 0.1;
		float mDiff;
		int mDrawedRoads;
		float cameraPos;
		bool stopped;
		bool started;
		bool gameover;

		std::shared_ptr<Managers::ShaderManager::Program> mProgramColor;
		std::shared_ptr<Managers::ShaderManager::Program> mProgramTexture;

		Graphics::spTexture mTextureFloor;
	};

	MAKE_SMART(GameScene);

}