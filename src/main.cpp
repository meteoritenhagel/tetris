//============================================================================
// Name        : tetris.cpp
// Author      : meteoritenhagel
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "falling.h"
#include "gameboard.h"
#include "renderingengine/renderingengine.h"
#include "shapes.h"
#include "types.h"

#include <SDL.h>

#include <iostream>

//void text_render()
//{
//	std::cout << "          ------------\n";
//	for (SizeType i = 0; i < height; ++i)
//	{
//		std::cout << "          <";
//		for (SizeType j = 0; j < width; ++j)
//		{
//			const char character = (get_cell_state(i,j)) ? '#' : ' ';
//			std::cout << character;
//		}
//		std::cout << '>' << "  CIR: " << (int) _cellsInRow[i] << '\n';
//	}
//	std::cout << "          ------------\n";
//	// reset_lines(height + 2);
//}

//void clean_screen()
//{
//	printf("\033c");
//}

using ColourType = uint8_t;

ColourType convert_state_to_colour(const CellState state)
{
	return state;
}

template<SizeType height, SizeType width>
bool events(GameBoard<height, width> &gameBoard)
{
	bool quit = false;
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
			quit = true;

		switch(event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = true;
				break;
			case SDLK_LEFT:
				gameBoard.move_left_if_valid();
				break;
			case SDLK_RIGHT:
				gameBoard.move_right_if_valid();
				break;
			case SDLK_DOWN:
				gameBoard.move_down_if_valid();
				break;
			case SDLK_r:
				gameBoard.rotate_if_valid();
				break;
			default:
				break;
			}
			break;
			default:
				break;
		}
	}
	return quit;
}

template<SizeType height, SizeType width>
void loop(GameBoard<height, width> &gameBoard)
{
	static uint8_t cycleCounter = 0;
	SDL_Delay(16);

	if (cycleCounter == 60)
	{
		gameBoard.update();
		cycleCounter = 0;
	}
	++cycleCounter;
}

template<SizeType height, SizeType width>
void render(GameBoard<height, width> &gameBoard, RenderingEngine &renderingEngine, SDL_Texture *texture)
{
	ColourType *pixelData;
	int pitch = 0;

	SDL_LockTexture(texture, NULL, reinterpret_cast<void**>(&pixelData), &pitch);
	int offset = pitch/sizeof(*pixelData);

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			const CellState currentState = gameBoard.get_cell_state(i, j);
			//pixelData[(i+1)*offset + j+3] = (currentState == CS_DEAD) ? (0x00222222 + ((i+j) % 2)*0x00111111) : COLOUR_TABLE[currentState];
			pixelData[(i+1)*offset + j+3] = (currentState == CS_DEAD) ? (0b00100000+ ((i+j) % 2)*0b00100000) : convert_state_to_colour(currentState);
		}
	}

	SDL_UnlockTexture(texture);
	SDL_RenderCopy(renderingEngine.getRenderer(), texture, NULL, NULL);
	SDL_RenderPresent(renderingEngine.getRenderer());
	return;
}

int main()
{
	GameBoard<> gameBoard;

	constexpr int screenWidth = 1000;
	constexpr int screenHeight = 1000;

	constexpr int gridWidth = 30;
	constexpr int gridHeight = 30;

	RenderingEngine renderingEngine(screenWidth, screenHeight, "Tetris");
	SDL_Texture *texture = SDL_CreateTexture(renderingEngine.getRenderer(), SDL_PIXELFORMAT_RGB332, SDL_TEXTUREACCESS_STREAMING, gridWidth, gridHeight);

	bool quit = false;

	render(gameBoard, renderingEngine, texture);
	while(!quit)
	{
		quit = events(gameBoard);
		loop(gameBoard);
		render(gameBoard, renderingEngine, texture);
	}

	return 0;
}
