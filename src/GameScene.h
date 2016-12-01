#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Engine/Scenes/Scene.h"
#include "Engine/Models/Floor.h"
#include "Player.h"
#include "Engine/Application.h"
#include "Car.h"

namespace Scenes {

	class GameScene : public Scene {
	public:
		explicit GameScene();
		virtual ~GameScene();

		void show() override;
		void resume() override;
		void pause() override;
		void hide() override;
		void update() override;

	private:
		void drawOneFloor();

		std::vector<Models::spFloor> mFloors;
		std::vector<spCar> mCars;
		spPlayer mPlayer;

		static const int FLOORS_COUNT = 24;
		const float SPEED_CONS = 1.5;
		int mDrawedRoads;
		float cameraPos;
		bool stopped;
		bool gameover;

		Managers::ShaderManager::Program mProgramColor;
		Managers::ShaderManager::Program mProgramTexture;

		Graphics::spTexture mTextureFloor; 
		Graphics::spTexture mTextureCube;
	};

	MAKE_SMART(GameScene);

}