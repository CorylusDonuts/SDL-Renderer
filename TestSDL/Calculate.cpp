#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Utils.h"
#include "RenderWindow.h"
#include "Calculate.h"

#define log(x) std::cout << x << std::endl

int Calculate::stuff(int width, int height, float frameTime){
	int size = 4 * width * height;
	buffer = new Uint8[size * 4];

	
	return utils::get(*buffer);
}
