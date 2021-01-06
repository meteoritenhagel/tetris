#include "main_auxiliary.h"

#include "tetris/gameboard.h"

#include <cstdlib>

int main()
{
    initialize_ncurses();

    GameBoard<24, 10> gameBoard;

    // the main loop exits as soon as the events loop returns true
    render_game(gameBoard);
    while (!events(gameBoard) && !gameBoard.is_game_over())
    {
        loop(gameBoard);
        render_game(gameBoard);
    }

    if (gameBoard.is_game_over())
    {
        render_game_over();
    }

    finalize_ncurses();

    return EXIT_SUCCESS;
}
