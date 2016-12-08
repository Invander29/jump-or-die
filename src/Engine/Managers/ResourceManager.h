//
// Created by invander on 24.10.16.
//

#pragma once

#include <unordered_map>
#include "../Graphics/Texture.h"
#include "../Graphics/Model.h"
#include "../../Images/Images.h"

namespace Managers {

	/**
	 * Managing resources (textures, audio, ...)
	 */
	class ResourceManager {
	public:
		explicit ResourceManager();
		~ResourceManager();

		/**
		 * Create or get texture from file
		 * @param filename path to texture
		 * @return spTexture
		 */
		Graphics::spTexture texture(const std::string& filename);

		/**
		 * Create or get texture from data
		 * @param name name of the texture
		 * @param image data of texture
		 * @return spTexture
		 */
		Graphics::spTexture texture(const std::string& name, Image* image);

		/**
		 * Delete texture
		 * @param filename path to texture
		 * @return true on success
		 */
		bool deleteTexture(const std::string& filename);

		/**
		 * Clear all loaded textures
		 */
		void clearTextures();

		/**
		 * Create or get model from file / from its built-in name
		 * @param filename name or id of model
		 */
		Graphics::spModel model(const std::string& filename);

		/**
		 * Remove model by it's name
		 * @filename name or id of model
		 * @return true on success
		 */
		bool deleteModel(const std::string& filename);

		/**
		 * Clear all models
		 */
		void clearModels();

	private:
		static const std::string folderImages;
		std::unordered_map<std::string, Graphics::spTexture> mTextures;
		std::unordered_map<std::string, Graphics::spModel> mModels;
	};

}
