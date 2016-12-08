#pragma once

#include "ModelObject.h"
#include "../Graphics/Texture.h"
#include "../Graphics/Model.h"
#include "../../Images/Images.h"

namespace Models {

	/**
	 * Simple abstract model which is represented by .obj file
	 */
	class ModelObj : public ModelObject
	{
	public:
		/**
		 * Create from Program, .obj, Texture
		 * @param program program
		 * @param obj object file
		 * @param image image data
		 */
		explicit ModelObj(std::shared_ptr<Managers::ShaderManager::Program> program, const std::string& obj, Image* image);

		/**
		 * Create from Program, .obj, Color
		 * @param program program
		 * @param obj object file
		 * @param r red color
		 * @param g green color
		 * @param b blue color
		 */
		explicit ModelObj(std::shared_ptr<Managers::ShaderManager::Program> program, const std::string& obj, float r, float g, float b);

		/**
		 * Descructor
		 */
		virtual ~ModelObj();

		/**
		 * Draw
		 */
		void draw(Scenes::Scene* scene) override;

	protected:
		Graphics::spTexture mTexture = nullptr;
		Graphics::spModel mModel = nullptr;

		Uniform mUniTexture;
		Uniform mUniColor;

		glm::vec3 mColor;
	};

}
