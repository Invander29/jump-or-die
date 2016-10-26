//
// Created by invander on 22.10.16.
//

#pragma once

#include <string>

namespace Utils {

	/**
	 * Read file
	 */
	class FileReader {
	public:
		/**
		 * Read file
		 * @param filename path to file
		 * @return content of file
		 */
		std::string readFile(const std::string& filename);

	private:
		std::string mFilename;
		std::string mContent;
	};

}