//
// Created by invander on 24.10.16.
//

#include "ResourceManager.h"
#include "../Graphics/Texture.h"
#include "../Utils/Utils.h"

using namespace Managers;
using namespace Graphics;
using namespace std;

ResourceManager::ResourceManager() {

}

ResourceManager::~ResourceManager() {
	clearTextures();
}

spTexture ResourceManager::getTexture(const std::string &filename)
{
	// Load old from memory
	unordered_map<string, spTexture>::iterator it = mTextures.find(filename);
	if (it != mTextures.end()) {
		return it->second;
	}

	// Load new from disk
	spTexture texture = make_shared<Texture>();
	if (!texture->fromFile(filename)) {
		Utils::error("Cannot load texture %s", filename.c_str());
		return texture;
	}

	mTextures[filename] = texture;
	return texture;
}

bool ResourceManager::deleteTexture(const std::string &filename) {
	unordered_map<string, spTexture>::const_iterator it = mTextures.find(filename);
	if (it == mTextures.end()) {
		return false;
	}

	mTextures.erase(it);
	return true;
}

void ResourceManager::clearTextures() {
	mTextures.clear();
}
