#include "Message.h"
#include "Basics.h"
#include <cstdarg>
#include <cstdio>
#include <vector>

using namespace Utils;

void Message::errorGL(const char* file, int line, GLuint object, const char* format, ...)
{
	fprintf(stderr, "Error [%s:%d]: ", file, line);

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

	std::vector<char> buffer(length);

	if (glIsShader(object)) {
		glGetShaderInfoLog(object, length, nullptr, buffer.data());
	} else if (glIsProgram(object)) {
		glGetProgramInfoLog(object, length, nullptr, buffer.data());
	}

	fprintf(stderr, "\n  OpenGL: %s\n", buffer.data());

	// Write to file
	FILE* f;
#ifdef WINDOWS
	fopen_s(&f, "error.txt", "a");
#else
	f = fopen("error.txt", "a");
#endif

	if (f != nullptr) {
		va_start(argptr, format);
		vfprintf(f, format, argptr);
		va_end(argptr);
		fprintf(f, "\n");

		fprintf(f, "  OpenGL: %s\n", buffer.data());
		fclose(f);
	}
}

bool Message::error(const char* file, int line, const char* format, ...)
{
	fprintf(stderr, "Error [%s:%d]: ", file, line);

	va_list argptr;
	va_start(argptr, format);
	vfprintf(stderr, format, argptr);
	va_end(argptr);

	fprintf(stderr, "\n");
	
	// Write to file
	FILE* f;
#ifdef WINDOWS
	fopen_s(&f, "error.txt", "a");
#else
	f = fopen("error.txt", "a");
#endif

	if (f != nullptr) {
		va_start(argptr, format);
		vfprintf(f, format, argptr);
		va_end(argptr);
		fprintf(f, "\n");
		fclose(f);
	}

	return false;
}

int Message::error(const char* file, int line, int code, const char* format, ...)
{
	fprintf(stderr, "Error [%s:%d (%d)]: ", file, line, code);

	va_list argptr;
	va_start(argptr, format);
	vfprintf(stderr, format, argptr);
	va_end(argptr);

	fprintf(stderr, "\n");

	// Write to file
	FILE* f;
#ifdef WINDOWS
	fopen_s(&f, "error.txt", "a");
#else
	f = fopen("error.txt", "a");
#endif

	if (f != nullptr) {
		va_start(argptr, format);
		vfprintf(f, format, argptr);
		va_end(argptr);
		fprintf(f, "\n");
		fclose(f);
	}

	return code;
}

void Message::debug(const char* format, ...)
{
#ifdef _DEBUG
	fprintf(stdout, "Debug: ");

	va_list argptr;
	va_start(argptr, format);
	vfprintf(stdout, format, argptr);
	va_end(argptr);

	fprintf(stdout, "\n");

	// Write to file
	FILE* f;
#ifdef WINDOWS
	fopen_s(&f, "debug.txt", "a");
#else
	f = fopen("debug.txt", "a");
#endif

	if (f != nullptr) {
		va_start(argptr, format);
		vfprintf(f, format, argptr);
		va_end(argptr);
		fprintf(f, "\n");
		fclose(f);
	}
#endif
}
