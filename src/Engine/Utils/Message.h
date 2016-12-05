#pragma once

#include <GL/gl3w.h>

namespace Utils {

	class Message {
	public:
		/**
		 * Print error from OpenGL
		 * @param object OpenGL error
		 * @param format printf format
		 */
		static void errorGL(const char* file, int line, GLuint object, const char *format, ...);

		/**
		 * Print error
		 * @param format printf format
		 */
		static bool error(const char* file, int line, const char *format, ...);

		/**
		* Print error
		* @param format printf format
		*/
		static int error(const char* file, int line, int code, const char *format, ...);

		/**
		 * Print debug information
		 * @param format printf format
		 */
		static void debug(const char *format, ...);
	};

}