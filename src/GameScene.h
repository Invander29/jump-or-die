#pragma once

#include <vector>
#include "Engine/Scenes/Scene.h"
#include "Engine/Models/Floor.h"
#include "Engine/Models/Player.h"
#include "Engine/Core.h"

#define FLOORS_COUNT 20 

namespace Scenes {

	class GameScene : public Scene {
	private:
		std::vector<Models::spFloor> floors;
		Models::spPlayer player;
		int player_pos;
		int drawed_roads;
		GLuint progSimpleColor;
		GLuint progSimpleTexture;
		Graphics::spTexture texFloor;
		virtual void drawOneFloor();

	public:
		explicit GameScene();

		virtual ~GameScene();

		virtual void show() override;

		virtual void resume() override;

		virtual void pause() override;

		virtual void hide() override;

		virtual void update() override;
	};

	MAKE_SMART(GameScene);

}