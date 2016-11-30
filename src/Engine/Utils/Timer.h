#pragma once

#include <chrono>

namespace Utils {

	/**
	 * Simple timer to get elapsed time
	 */
	class Timer {
	public:
		explicit Timer();
		~Timer();

		/**
		 * Get elapsed time from last call of this function
		 * @return delta time
		 */
		double delta();

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> mTime;
	};

}