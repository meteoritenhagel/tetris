/*
 * RenderingEngine.h
 *
 *  Created on: Oct 18, 2020
 *      Author: tristan
 */

#ifndef RENDERINGENGINE_H_
#define RENDERINGENGINE_H_

#include <SDL.h>

#include <string>

class RenderingEngine {
public:
	RenderingEngine(const int width, const int height, const std::string title);
	virtual ~RenderingEngine();

	SDL_Window* getWindow() const;
	SDL_Renderer* getRenderer() const;

private:
	int _width;
	int _height;
	SDL_Window* _window;
	SDL_Renderer* _renderer;
};

#endif /* RENDERINGENGINE_H_ */
