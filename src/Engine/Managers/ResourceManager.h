//
// Created by invander on 24.10.16.
//

#pragma once

#include <unordered_map>
#include "../Graphics/Texture.h"
#include "../Graphics/Model.h"

namespace Managers {

	/**
	 * Managing resources (textures, audio, ...)
	 */
	class ResourceManager {
	public:
		explicit ResourceManager();
		~ResourceManager();

		/**
		 * Create or get texture
		 * @param filename path to texture
		 * @return spTexture
		 */
		Graphics::spTexture texture(const std::string& filename);

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

		Graphics::spModel model(const std::string& filename);
		bool deleteModel(const std::string& filename);
		void clearModels();

	private:
		static const std::string folderImages;
		std::unordered_map<std::string, Graphics::spTexture> mTextures;
		std::unordered_map<std::string, Graphics::spModel> mModels;
	};

}
