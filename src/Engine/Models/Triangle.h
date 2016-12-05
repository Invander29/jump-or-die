#pragma once
#include "ModelObject.h"

namespace Models {

	class Triangle : public Models::ModelObject
	{
	public:
		explicit Triangle(std::shared_ptr<Managers::ShaderManager::Program> program);

		void update() override;
		void draw(Scenes::Scene* scene) override;
	};

	MAKE_SMART(Triangle);
}