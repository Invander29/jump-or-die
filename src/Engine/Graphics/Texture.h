//
// Created by invander on 24.10.16.
//

#pragma once

#include <vector>
#include <GL/gl3w.h>

#include "../Utils/Basics.h"

namespace Graphics {

	/**
	 * Structure containing texture data, loading it to memory, register to OpenGL
	 */
	class Texture {
	public:
		explicit Texture();
		~Texture();

		/**
		 * Load from file and register to OpenGL
		 * @param filename name of file
		 * @return true if success
		 */
		bool fromFile(const std::string& filename);

		/**
		 * Load from data and register to OpenGL
		 * @param name id of texture
		 * @param data data of texture
		 * @param width width of texture
		 * @param height height of texture
		 * @param format format of texture (number of bytes per pixel = 3 for RGB and 4 for RGBA)
		 * @return true if success
		 */
		bool fromData(const std::string& name, unsigned char* data, unsigned int width, unsigned int height, unsigned int format);

		/**
		 * Get name of the texture
		 */
		const std::string& name() const { return mName; }

		/**
		 * Set name of the texture
		 */
		void setName(const std::string& name) { mName = name; }

		/**
		 * Set filters for texture
		 */
		void setFilter(GLenum minFilter, GLenum magFilter);

		/**
		 * Set min filter
		 * @param filter MIN
		 */
		void setMinFilter(GLenum filter);

		/**
		 * Set mag filter
		 * @param filter MAG
		 */
		void setMagFilter(GLenum filter);

		/**
		 * Set wrapping
		 * @param s type per X
		 * @param t type per Y
		 */
		void setWrapping(GLenum s, GLenum t);

		/**
		 * Generate mipmap from loaded texture
		 * @param minFilter MIN MIPMAP filter
		 * @param magFilter MAG MIPMAP filter
		 */
		void generateMipMap(GLenum minFilter = GL_NEAREST_MIPMAP_NEAREST, GLenum magFilter = GL_NEAREST_MIPMAP_NEAREST);

		/**
		 * Get ID of texture in OpenGL
		 */
		GLuint id() const { return mId; }

		/**
		 * Get Width of texture
		 */
		int width() const { return mWidth; }

		/**
		 * Get height of texture
		 */
		int height() const { return mHeight; }

		/**
		 * Get format of texture
		 */
		GLenum format() const { return mFormat; }

		/**
		 * Get type of data in texture
		 */
		GLenum type() const { return mType; }

	private:
		/**
		 * Create texture in OpenGL
		 * @param data texture raw data
		 */
		void registerSelf(unsigned char* data);

		/**
		 * Delete texture from OpenGL
		 */
		void unregisterSelf();

		unsigned int mWidth = 0;
		unsigned int mHeight = 0;

		std::string mName;

		GLuint mId = 0;
		GLenum mMinFilter = GL_LINEAR;
		GLenum mMagFilter = GL_LINEAR;
		GLenum mFormat = GL_RGBA;
		GLenum mType = GL_UNSIGNED_BYTE;
	};

	MAKE_SMART(Texture);
}