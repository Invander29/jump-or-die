#pragma once

#include "Engine/Scenes/Scene.h"

namespace Scenes {

	class GameScene : public Scene {
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