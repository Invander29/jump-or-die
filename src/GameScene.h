#pragma once

#include <vector>
#include "Engine/Scenes/Scene.h"
#include "Engine/Models/Floor.h"
#include "Player.h"
#include "Engine/Application.h"

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
		spPlayer mPlayer;

		static const int FLOORS_COUNT = 20;
		int mDrawedRoads;

		std::shared_ptr<Managers::ShaderManager::Program> mProgramColor;
		std::shared_ptr<Managers::ShaderManager::Program> mProgramTexture;

		Graphics::spTexture mTextureFloor; 
		Graphics::spTexture mTextureCube;
	};

	MAKE_SMART(GameScene);

}