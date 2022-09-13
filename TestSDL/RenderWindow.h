#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#define log(x) std::cout << x << std::endl

class RenderWindow {
public:
	RenderWindow(const char* title, int w, int h);
	void cleanUp();
	void clear();
	void render(SDL_Surface* surface, SDL_Rect* rect);
	void display();
	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;
};