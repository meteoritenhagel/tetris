#ifndef TETRIS_MAIN_AUXILIARY_H
#define TETRIS_MAIN_AUXILIARY_H

#include "tetris/falling.h"
#include "tetris/gameboard.h"
#include "tetris/shapes.h"
#include "tetris/types.h"

#include <ncurses.h>


using ColourType = short;

/*
 * Initializes the ncurses color pairs.
 * They can be used via COLOR_PAIR(color_index), where color_index is a number between 0 and 7.
 */
void initialize_colors();

/*
 * Converts the cell state to a color.
 * Since ncurses has 8 colors, a state of 0 is mapped to black and all other states are mapped to colors except black.
 *
 * @param[in] state The state of the cell
 * @return          The color representation of the state
 */
ColourType convert_state_to_color(const CellState state);

/*
 * Event loop implementatation. Captures key events and reacts accordingly.
 *
 * @param[in] gameBoard the current tetris game board
 * @return bool indicating whether program should be terminated
 */
template<SizeType height, SizeType width>
bool events(GameBoard<height, width> &gameBoard);

/*
 * Game loop implementation. Updates the game board in dependence on the current game progress.
 * @param[in] gameBoard the current tetris game board
 */
template<SizeType height, SizeType width>
void loop(GameBoard<height, width> &gameBoard);

/*
 * Draws a fancy horizontal line of specified width in an ncurses window.
 * @param[in] window ncurses window
 * @param[in] width width of line
 */
void draw_horizontal_line(WINDOW * const window, const int width);

/*
 * Render loop implementation for the tetris game.
 * It renders the game board and an information board separately.
 * @param[in] gameBoard the current tetris game board
 */
template<SizeType height, SizeType width>
void render_game(const GameBoard<height, width> &gameBoard);

/*
 * Displays the "GAME OVER" message.
 */
void render_game_over();

/*
 * Initializes the ncurses library and the used colors. When using ncurses, proper initialization is necessary.
 */
void initialize_ncurses();

/*
 * Restores the original terminal settings. Before exiting the program, proper cleanup of ncurses' settings
 * is necessary.
 */
void finalize_ncurses();

#include "main_auxiliary.hpp"

#endif //TETRIS_MAIN_AUXILIARY_H
