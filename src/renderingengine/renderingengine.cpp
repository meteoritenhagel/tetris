/*
 * RenderingEngine.cpp
 *
 *  Created on: Oct 18, 2020
 *      Author: tristan
 */

#include <cassert>
#include <iostream>
#include <string>

#include "renderingengine.h"

RenderingEngine::RenderingEngine(const int width, const int height, const std::string title)
: _width(width), _height(height)
{
	bool status = SDL_Init(SDL_INIT_VIDEO);
	assert(status == 0 && "ERROR: SDL initialization failed.");

	_window = SDL_CreateWindow(title.c_str(), 100, 100, width, height, SDL_WINDOW_SHOWN);
	if (_window == nullptr)
	{
		std::cout << "ERROR: SDL_CreateWindow failed." << std::endl;
		SDL_Quit();
		exit(-1);
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (_renderer == nullptr)
	{
		SDL_DestroyWindow(_window);
		std::cout << "ERROR: SDL_CreateRenderer failed." << std::endl;
		SDL_Quit();
		exit(-1);
	}
}

RenderingEngine::~RenderingEngine()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

SDL_Window* RenderingEngine::getWindow() const
{
	return _window;
}

SDL_Renderer* RenderingEngine::getRenderer() const
{
	return _renderer;
}

