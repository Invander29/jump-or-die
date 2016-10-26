#include "Utils.h"
#include <cstdarg>

void Utils::errorSDL(const char* format, ...)
{
	fprintf(stderr, "Error: ");

	va_list argptr;
	va_start(argptr, format);
	vfprintf(stderr, format, argptr);
	va_end(argptr);

	fprintf(stderr, "\n  SDL message: %s\n", SDL_GetError());
}

void Utils::errorGL(GLuint object, const char* format, ...)
{
	fprintf(stderr, "Error: ");

	va_list argptr;
	va_start(argptr, format);
	vfprintf(stderr, format, argptr);
	va_end(argptr);

	// OpenGL info
	GLint length = 0;
	if (glIsShader(object)) {
		glGetShaderiv(object, GL_INFO_LOG_LENGTH, &length);
	} else if (glIsProgram(object)) {
		glGetProgramiv(object, GL_INFO_LOG_LENGTH, &length);
	} else {
		fprintf(stderr, "\n  OpenGL: GameObject is not a shader or program\n");
	}

	char* buffer = new char[length];
	if (glIsShader(object)) {
		glGetShaderInfoLog(object, length, nullptr, buffer);
	} else if (glIsProgram(object)) {
		glGetProgramInfoLog(object, length, nullptr, buffer);
	}

	fprintf(stderr, "\n  OpenGL: %s\n", buffer);
	delete[] buffer;
}

void Utils::error(const char* format, ...)
{
	fprintf(stderr, "Error: ");

	va_list argptr;
	va_start(argptr, format);
	vfprintf(stderr, format, argptr);
	va_end(argptr);

	fprintf(stderr, "\n");
}

void Utils::debug(const char* format, ...)
{
	fprintf(stdout, "Debug: ");

	va_list argptr;
	va_start(argptr, format);
	vfprintf(stdout, format, argptr);
	va_end(argptr);

	fprintf(stdout, "\n");
}
