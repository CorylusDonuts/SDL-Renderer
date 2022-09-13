#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <future>

#include "Utils.h"
#include "RenderWindow.h"

class Calculate {
public:
	Calculate(int w, int h);
	void move(bool isX, bool isAdd);
	void scaleCam(bool isZoomIn);
	void scaleIter(bool isIncrease);
	void stuff(char* pixels);
	void mandelbrot(char* pixels);
private:
	int width;
	int height;
	float camx;
	float camy;
	float dr;
	float scale;
	float scaleRatio;
	int maxIter;
};