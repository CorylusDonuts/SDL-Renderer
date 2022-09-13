#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <future>

#include "Utils.h"
#include "RenderWindow.h"
#include "calculate.h"

#define log(x) std::cout << x << std::endl

int main(int argv, char* args[]) {
	int width = 1000;
	int height = 500;

	if (SDL_Init(SDL_INIT_VIDEO) > 0) 
		log("SDL_Init Error: " << SDL_GetError());
	RenderWindow window("program", width, height);

	//Screen Rectangle
	SDL_Rect screen;
	screen.x = 0;
	screen.y = 0;
	screen.w = width;
	screen.h = height;
	//initiate camera
	float x = -(float)width/2;
	float y = -(float)height/2;
	float scale = 1;

	int iter = 50;


	SDL_Event event;

	const float timeStep = 13.888889;
	float accumulator = 0.0f;
	float currentTime = utils::timeElapsed();

	bool programRunning = true;

	while (programRunning) {
		float newTime = utils::timeElapsed();
		float frameTime = newTime - currentTime;

		currentTime = newTime;

		accumulator += frameTime;
		
		while (accumulator >= timeStep) {
			
			//Handle events
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT)
					programRunning = false;
				const Uint8* state = SDL_GetKeyboardState(NULL);
				if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]) {
					x += height/scale;
					log("right");
				}
				if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]) {
					x -= height/scale;
					log("left");
				}
				if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) {
					y -= height/scale;
					log("up");
				}
				if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]) {
					y += height/scale;
					log("down");
				}
				if (state[SDL_SCANCODE_PERIOD] && event.key.repeat == 0) {
					scale *= 1.25; 
					log("zoom in");
				}
				if (state[SDL_SCANCODE_COMMA] && event.key.repeat == 0) {
					scale /= 1.25;
					log("zoom out");
				}
				if (state[SDL_SCANCODE_M] && event.key.repeat == 0) {
					iter *= 1.25;
					log("Increased Iterations");
				}
				if (state[SDL_SCANCODE_N] && event.key.repeat == 0) {
					iter /= 1.25;
					if (iter < 4)
						iter = 4;
					log("Decreased Iterations");
				}
			}
			//Update


			//Draw
			window.setColor(255, 255, 255, SDL_ALPHA_OPAQUE);
			window.clear();

			char* pixels = new char[width * height * 3];
			Calculate::mandelbrot(pixels, width, height, x, y, scale, iter);
			SDL_Surface* surface = SDL_CreateRGBSurfaceFrom((void*)pixels,
				width,
				height,
				3 * 8,		//3 channels * 8 bits per channel
				3 * width,	//pitch = channels * width
				0x0000ff,	//red mask
				0x00ff00,	//green mask
				0xff0000,	//blue mask
				0);			//alpha mask


			//Convert surface to texture, then render the texture
			window.render(surface, &screen);
			SDL_FreeSurface(surface);
			window.display();

			delete[] pixels;


			if (accumulator - timeStep < 0) {
				accumulator -= timeStep;
			}
			else {
				accumulator = 0;
			}
		}
		float frameTicks = SDL_GetTicks() - newTime;
		if (timeStep > frameTicks) {
			SDL_Delay(timeStep - frameTicks);
		}
		//For Frame Time
		//log(SDL_GetTicks() - newTime);
	}
	window.cleanUp();
	SDL_Quit();

	return 0;
}