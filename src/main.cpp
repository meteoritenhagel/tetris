#include "falling.h"
#include "gameboard.h"
#include "renderingengine/renderingengine.h"
#include "shapes.h"
#include "types.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include <cstdlib>
#include <iostream>

void clean_screen()
{
    printf("\033c");
}

template<SizeType height, SizeType width>
void render_console(const GameBoard<height, width> &gameBoard)
{
    std::cout << "          ------------\n";
    for (SizeType i = 0; i < height; ++i)
    {
        std::cout << "          <";
        for (SizeType j = 0; j < width; ++j)
        {
            const char character = (gameBoard.get_cell_state(i, j)) ? '#' : ' ';
            std::cout << character;
        }
        std::cout << "> " << std::endl;
    }
    std::cout << "          ------------\n";
    clean_screen();
}

using ColourType = uint8_t;

/*
 * Converts the cell state to a colour.
 * Since for the current implementation the colour is expressed via RGB332
 * the state and the colour coincide.
 * As soon as a real conversion is needed (i.e. for ARGB3333),
 * this function needs to be changed.
 *
 * @param[in] state The state of the cell
 * @return          The colour representation of the state
 */
ColourType convert_state_to_colour(const CellState state)
{
    return state;
}


/*
 * Event loop implementatation
 *
 * @param[in] gameBoard the current tetris game board
 * @return bool indicating whether program should be terminated
 */
template<SizeType height, SizeType width>
bool events(GameBoard<height, width> &gameBoard)
{
    bool quit = false;
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            quit = true;

        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
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
                        gameBoard.rotate_clockwise_if_valid();
                        break;
                    case SDLK_u:
                        gameBoard.rotate_counterclockwise_if_valid();
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

/*
 * Game loop implementation
 * @param[in] gameBoard the current tetris game board
 */
template<SizeType height, SizeType width>
void loop(GameBoard<height, width> &gameBoard)
{
    static uint8_t cycleCounter = 0;

    // 16ms delay ~= 60 FPS
    SDL_Delay(16);

    // Game board gets updated after certain number of cycles
    // When having 60 FPS, an update cycle threshold of 60
    // corresponds to one update per second
    if (cycleCounter == gameBoard.get_update_cycle_threshold())
    {
        gameBoard.update();
        cycleCounter = 0;
    }
    ++cycleCounter;
}

/*
 * Render loop implementation.
 * If compiled with -DMODE_SDL, the game is rendered using SDL.
 * If compiled without that flag, the game is rendered in the console.
 * @param[in] gameBoard the current tetris game board
 */
template<SizeType height, SizeType width>
void render(const GameBoard<height, width> &gameBoard)
{
#ifdef MODE_SDL
   render_sdl(gameBoard);
#else
   render_console(gameBoard);
#endif
}
template<SizeType height, SizeType width>
void render_sdl(const GameBoard<height, width> &gameBoard)
{
    static constexpr int screenWidth = 800;
    static constexpr int screenHeight = 800;

    static constexpr int gridWidth = 30;
    static constexpr int gridHeight = 30;

    static RenderingEngine renderingEngine(screenWidth, screenHeight, "Tetris");
    static SDL_Texture *frameBuffer = SDL_CreateTexture(renderingEngine.getRenderer(),
                                                    SDL_PIXELFORMAT_RGB332,
                                                    SDL_TEXTUREACCESS_STREAMING,
                                                    gridWidth,
                                                    gridHeight);

    ColourType *pixelData;

    // length of a surface scanline in bytes
    int pitch;
    SDL_LockTexture(frameBuffer, NULL, reinterpret_cast<void**>(&pixelData), &pitch);

    // length of a surface scanline in pixels
    int offset = pitch / sizeof(*pixelData);

    // iterate through all game board cells and modify frame buffer accordingly
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            const CellState currentState = gameBoard.get_cell_state(i, j);
            //pixelData[(i+1)*offset + j+3] = (currentState == CS_DEAD) ? (0x00222222 + ((i+j) % 2)*0x00111111) : COLOUR_TABLE[currentState];
            pixelData[(i + 1) * offset + j + 3] =
                    (currentState == CS_DEAD) ?
                            (0b00100000 + ((i + j) % 2) * 0b00100000) :
                            convert_state_to_colour(currentState);
        }
    }

    SDL_UnlockTexture(frameBuffer);
    // copies frame buffer into renderer
    SDL_RenderCopy(renderingEngine.getRenderer(), frameBuffer, NULL, NULL);
    SDL_RenderPresent(renderingEngine.getRenderer());
    return;
}

int main()
{
    GameBoard<> gameBoard;

    // the main loop exits as soon as the events loop returns true
    render(gameBoard);
    while (!events(gameBoard))
    {
        loop(gameBoard);
        render(gameBoard);
    }

    return EXIT_SUCCESS;
}
