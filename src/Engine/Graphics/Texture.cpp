//
// Created by invander on 24.10.16.
//

#include <lodepng/lodepng.h>
#include "Texture.h"
#include "../Utils/Message.h"

using namespace Utils;

Graphics::Texture::Texture() {

}

Graphics::Texture::~Texture() {
	Message::debug("Deleting texture %d", mId);
	unregisterSelf();
}

bool Graphics::Texture::fromFile(const std::string &filename)
{
	Message::debug("Loading texture %s", filename.c_str());

	std::vector<unsigned char> data;
	unsigned int error = lodepng::decode(data, mWidth, mHeight, filename);
	if (error != 0) {
		Message::error(__FILE__, __LINE__, "Cannot load texture: %s", lodepng_error_text(error));
		return false;
	}

	mName = filename;
	registerSelf(&data[0]);

	Message::debug("Texture is registered as: %s / %d", filename.c_str(), mId);
	return true;
}


void Graphics::Texture::setFilter(GLenum minFilter, GLenum magFilter)
{
	if (mId != 0) {
		mMinFilter = minFilter;
		mMagFilter = magFilter;
		glBindTexture(GL_TEXTURE_2D, mId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	}
}

void Graphics::Texture::setMinFilter(GLenum filter)
{
	if (mId != 0) {
		mMinFilter = filter;
		glBindTexture(GL_TEXTURE_2D, mId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mMinFilter);
	}
}

void Graphics::Texture::setMagFilter(GLenum filter)
{
	if (mId != 0) {
		mMagFilter = filter;
		glBindTexture(GL_TEXTURE_2D, mId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mMagFilter);
	}
}

void Graphics::Texture::setWrapping(GLenum s, GLenum t)
{
	if (mId != 0) {
		glBindTexture(GL_TEXTURE_2D, mId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t);
	}
}

void Graphics::Texture::generateMipMap(GLenum minFilter, GLenum magFilter)
{
	mMinFilter = minFilter;
	mMagFilter = magFilter;

	if (mId != 0) {
		glBindTexture(GL_TEXTURE_2D, mId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mMagFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mMinFilter);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}

void Graphics::Texture::registerSelf(unsigned char* data)
{
	glGenTextures(1, &mId);
	glBindTexture(GL_TEXTURE_2D, mId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mMinFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mMagFilter);
	glTexImage2D(GL_TEXTURE_2D,
	             0, //level - 0 = base, no mipmap
	             mFormat, // internal format,
	             mWidth,
	             mHeight,
	             0, // border
	             mFormat, // format,
	             mType, // type,
	             data);
}

void Graphics::Texture::unregisterSelf()
{
	if (mId != 0) {
		glDeleteTextures(1, &mId);
		mId = 0;
	}
}
