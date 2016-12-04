#pragma once
#include "ModelObject.h"
#include "../Graphics/Texture.h"
#include "../Graphics/Model.h"

namespace Models {

	class ModelObj : public ModelObject
	{
	public:
		explicit ModelObj(std::shared_ptr<Managers::ShaderManager::Program> program, const std::string& obj, const std::string& texture);
		virtual ~ModelObj();

		void draw(Scenes::Scene* scene) override;

	protected:
		Graphics::spTexture mTexture;
		Graphics::spModel mModel;

		Uniform mUniTexture;
	};

}
