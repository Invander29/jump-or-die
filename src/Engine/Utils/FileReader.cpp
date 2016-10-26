//
// Created by invander on 22.10.16.
//

#include <SDL2/SDL.h>
#include "FileReader.h"
#include "Utils.h"

using namespace Utils;

std::string FileReader::readFile(const std::string &filename)
{
	if (mFilename == filename) {
		return mContent;
	}

	SDL_RWops *file = SDL_RWFromFile(filename.c_str(), "r");
	if (file == nullptr) {
		Utils::errorSDL("Cannot open file %s", filename.c_str());
		return std::string();
	}

	// TODO conversion signed / unsigned!
	size_t size = SDL_RWsize(file);
	char* buffer = new char[size + 1];

	size_t readTotal = 0;
	size_t readCount = 1;
	char* ptr = buffer;
	while (readTotal < size && readCount != 0) {
		readCount = SDL_RWread(file, ptr, 1, size - readTotal);
		readTotal += readCount;
		ptr += readCount;
	}

	SDL_RWclose(file);
	if (readTotal != size) {
		delete[] buffer;
		Utils::error("ReadFile size doesn't match %d/%d", readTotal, size);
		return nullptr;
	}

	buffer[size] = '\0';
	mFilename = filename;
	mContent = buffer;
	return mContent;
}
