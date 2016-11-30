//
// Created by invander on 22.10.16.
//

#include "FileReader.h"
#include "Message.h"

#include <string>
#include <fstream>
#include<streambuf>

using namespace Utils;

std::string FileReader::readFile(const std::string &filename)
{
	if (mFilename == filename) {
		return mContent;
	}

	std::ifstream t(filename);
	if (!t.is_open()) {
		Message::error(__FILE__, __LINE__, "Cannot open a file %s", filename.c_str());
		return std::string();
	}

	mFilename = filename;
	mContent.clear();
	
	t.seekg(0, std::ios::end);
	mContent.reserve(t.tellg());
	t.seekg(0, std::ios::beg);

	mContent.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
	return mContent;
}
