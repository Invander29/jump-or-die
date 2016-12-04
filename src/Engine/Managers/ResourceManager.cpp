//
// Created by invander on 24.10.16.
//

#include "ResourceManager.h"
#include "../Graphics/Texture.h"
#include "../Utils/Message.h"

using namespace std;
using namespace Managers;
using namespace Graphics;
using namespace Utils;

const std::string ResourceManager::folderImages = "images/";

ResourceManager::ResourceManager() 
{
}

ResourceManager::~ResourceManager() 
{
	clearTextures();
}

spTexture ResourceManager::texture(const std::string &filename)
{
	std::string fullname = folderImages + filename;

	// Load old from memory
	unordered_map<string, spTexture>::iterator it = mTextures.find(fullname);
	if (it != mTextures.end()) {
		return it->second;
	}

	// Load new from disk
	spTexture texture = make_shared<Texture>();
	if (!texture->fromFile(fullname)) {
		Message::error(__FILE__, __LINE__, "Cannot load texture %s", fullname.c_str());
		return texture;
	}

	texture->generateMipMap();
	mTextures[fullname] = texture;
	return texture;
}

bool ResourceManager::deleteTexture(const std::string &filename) 
{
	std::string fullname = folderImages + filename;

	unordered_map<string, spTexture>::const_iterator it = mTextures.find(fullname);
	if (it == mTextures.end()) {
		return false;
	}

	mTextures.erase(it);
	return true;
}

void ResourceManager::clearTextures() {
	mTextures.clear();
}

spModel ResourceManager::model(const std::string &filename)
{
	std::string fullname = filename + ".obj";

	// Load old from memory
	unordered_map<string, spModel>::iterator it = mModels.find(fullname);
	if (it != mModels.end()) {
		return it->second;
	}

	// Load new from disk
	spModel model = make_shared<Model>();
	if (!model->load(fullname)) {
		Message::error(__FILE__, __LINE__, "Cannot load model %s", fullname.c_str());
		return model;
	}

	mModels[fullname] = model;
	return model;
}

bool ResourceManager::deleteModel(const std::string &filename)
{
	std::string fullname = filename + ".obj";

	unordered_map<string, spModel>::const_iterator it = mModels.find(fullname);
	if (it == mModels.end()) {
		return false;
	}

	mModels.erase(it);
	return true;
}

void ResourceManager::clearModels() {
	mModels.clear();
}