#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <memory>
#include <GL/glew.h>

#define MAKE_SMART(class) using sp ## class = std::shared_ptr<class>;
#define NEW_SMART(class,...) std::make_shared<class>(__VA_ARGS__);

#define SHOW_ERRORS
#define SHOW_DEBUG

namespace Utils {

#if defined(SHOW_ERRORS) || defined(SHOW_DEBUG)

	/**
	 * Print error from SDL
	 * @param format printf format
	 */
	void errorSDL(const char *format, ...);

	/**
	 * Print error from OpenGL
	 * @param object OpenGL error
	 * @param format printf format
	 */
	void errorGL(GLuint object, const char *format, ...);

	/**
	 * Print error
	 * @param format printf format
	 */
	void error(const char *format, ...);

#endif // SHOW ERRORS

#ifdef SHOW_DEBUG

	/**
	 * Print debug information
	 * @param format printf format
	 */
	void debug(const char *format, ...);

#endif // SHOW DEBUG

}