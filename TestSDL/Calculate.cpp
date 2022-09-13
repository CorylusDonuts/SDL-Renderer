#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <future>

#include "Utils.h"
#include "RenderWindow.h"
#include "calculate.h"

Calculate::Calculate(int w, int h) 
	:width(w), height(h)
{
	camx = 0;
	camy = 0;
	maxIter = 50;
	scale = 1;
	scaleRatio = 1.25;
	dr = (float)height / 8;
}
void Calculate::move(bool isX, bool isAdd) {
	if (isX) {
		if (isAdd)
			camx += dr;
		else
			camx -= dr;
	}
	else {
		if (isAdd)
			camy += dr;
		else
			camy -= dr;
	}
}

void Calculate::scaleCam(bool isZoomIn) {
	if (isZoomIn) {
		scale *= scaleRatio;
		camx *= scaleRatio;
		camy *= scaleRatio;
	}
	else {
		scale /= scaleRatio;
		camx /= scaleRatio;
		camy /= scaleRatio;
	}
}

void Calculate::scaleIter(bool isIncrease) {
	if (isIncrease) {
		maxIter *= scaleRatio;
	}
	else {
		maxIter /= scaleRatio;
		if (maxIter < 4)
			maxIter = 4;
	}
}

void Calculate::stuff(char* pixels) {
	int time = SDL_GetTicks();
	int num = width * height;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int index = 3 * (i + j * width);
			pixels[index + 0] = time / 2 + 255 * i / width;
			pixels[index + 1] = time / 4 + 255 * j / height;
			pixels[index + 2] = time + 255 * i * j / num;
		}
	}
}

void Calculate::mandelbrot(char* pixels) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {

			float x0 = (camx - (float)width / 2 + (float)i) / (scale * height);
			float y0 = (camy - (float)height / 2 + (float)j) / (scale * height);
			float x = 0;
			float y = 0;
			int n = 0;
			while (n < maxIter && x * x + y * y <= 4) {
				float xtemp = x * x - y * y + x0;
				y = 2 * x * y + y0;
				x = xtemp;
				n++;
			}
			int index = 3 * (i + j * width);
			pixels[index + 0] = 255 * (maxIter - n) / maxIter;
			pixels[index + 1] = 255 * (maxIter - n) / maxIter;
			pixels[index + 2] = 255 * (maxIter - n) / maxIter;
		}
	}
}
