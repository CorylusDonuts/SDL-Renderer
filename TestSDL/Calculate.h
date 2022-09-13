#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <future>

#include "Utils.h"
#include "RenderWindow.h"

namespace Calculate {
	inline void stuff(char* pixels, int width, int height, float camx, float camy, float scale) {
		int time = SDL_GetTicks();
		int num = width * height;
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				int index = 3 * (i + j * width);
				pixels[index + 0] = time/2 + 255 * i / width;
				pixels[index + 1] = time/4 + 255 * j / height;
				pixels[index + 2] = time + 255 * i * j / num;
			}
		}
	}
	
	inline void mandelbrot(char* pixels, int width, int height, float camx, float camy, float scale, int iter) {
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {

				float x0 = (scale*camx/4 - (float)width/2 + (float)i)/(scale*height) - 1;
				float y0 = (scale*camy/4 - (float)height/2 + (float)j)/(scale*height);
				float x = 0;
				float y = 0;
				int n = 0;
				while (n < iter && x * x + y * y <= 4) {
					float xtemp = x * x - y * y + x0;
					y = 2 * x * y + y0;
					x = xtemp;
					n++;
				}
				int index = 3 * (i + j * width);
				pixels[index + 0] = 255*(iter - n)/iter;
				pixels[index + 1] = 255 * (iter - n) / iter;
				pixels[index + 2] = 255 * (iter - n) / iter;
			}
		}
	}
};