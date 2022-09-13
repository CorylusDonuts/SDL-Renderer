#pragma once

#include <SDL.h>

namespace utils {
	inline float timeElapsed() {
		return (SDL_GetTicks());
	}
	inline int indexTwo(int x, int y) {
		return x * y + x;
	}
	inline int indexThree(int x, int y, int z) {
		return x * y * z + x * y + x;
	}

	inline int get(int num) {
		int number = num;
		return number;
	}
}