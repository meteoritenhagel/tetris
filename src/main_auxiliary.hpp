using ColourType = short;

void initialize_colors()
{
    init_pair(0, COLOR_RED, COLOR_RED);
    init_pair(1, COLOR_RED, COLOR_RED);
    init_pair(2, COLOR_GREEN, COLOR_GREEN);
    init_pair(3, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(4, COLOR_BLUE, COLOR_BLUE);
    init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(6, COLOR_CYAN, COLOR_CYAN);
    init_pair(7, COLOR_WHITE, COLOR_WHITE);
}

ColourType convert_state_to_color(const CellState state)
{
    ColourType colour = COLOR_BLACK;
    if (state != 0)
    {
        colour = state % 7 + 1;

    }
    return COLOR_PAIR(colour);
}

template<SizeType height, SizeType width>
bool events(GameBoard<height, width> &gameBoard)
{
    bool quit = false;

    int keystroke = getch();

    switch (keystroke)
    {
        case 'q':
            quit = true;
            break;
        case KEY_LEFT:
            gameBoard.move_left_if_valid();
            break;
        case KEY_RIGHT:
            gameBoard.move_right_if_valid();
            break;
        case KEY_DOWN:
            gameBoard.move_down_if_valid();
            break;
        case 'r':
            gameBoard.rotate_clockwise_if_valid();
            break;
        case 'u':
            gameBoard.rotate_counterclockwise_if_valid();
            break;
        default:
            break;
    }
    return quit;
}

template<SizeType height, SizeType width>
void loop(GameBoard<height, width> &gameBoard)
{
    static uint8_t cycleCounter = 0;

    // 16ms delay ~= 60 FPS
    napms(16);

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

void draw_horizontal_line(WINDOW * const window, const int width)
{
    wprintw(window, "-%s-", std::string(width-2, '=').c_str());
}

template<SizeType height, SizeType width>
void render_game(const GameBoard<height, width> &gameBoard)
{
    // first, render game board window
    constexpr int gameBoardWindowHeight = height + 2;
    constexpr int gameBoardWindowWidth = 2*width + 4;
    constexpr int gameBoardWindowY = 2;
    constexpr int gameBoardWindowX = 5;

    static WINDOW* gameBoardWindow = newwin(gameBoardWindowHeight, gameBoardWindowWidth, gameBoardWindowY, gameBoardWindowX);
    werase(gameBoardWindow);

    draw_horizontal_line(gameBoardWindow, gameBoardWindowWidth); // draw upper wall
    for (SizeType i = 0; i < height; ++i)
    {
        wprintw(gameBoardWindow, "<!");
        for (SizeType j = 0; j < width; ++j)
        {
            const CellState currentState = gameBoard.get_cell_state(i, j);
            const char character = currentState ? '#' : ' '; // print a character in case colors are not available

            wattron(gameBoardWindow, convert_state_to_color(currentState));
            wprintw(gameBoardWindow, "%c%c", character, character); // print twice to make the form more square
            wattroff(gameBoardWindow, convert_state_to_color(currentState));
        }
        wprintw(gameBoardWindow, "!>");
    }
    draw_horizontal_line(gameBoardWindow, gameBoardWindowWidth); // draw lower wall
    wrefresh(gameBoardWindow);

    // then, render info window
    constexpr int infoWindowHeight = gameBoardWindowHeight;
    constexpr int infoWindowWidth = 18;
    constexpr int infoWindowWindowY = gameBoardWindowY;
    constexpr int infoWindowWindowX = gameBoardWindowX + gameBoardWindowWidth;

    static_assert(height >= 24, "ERROR: Game board height must be greater or equal to 24.");
    static WINDOW* infoWindow = newwin(infoWindowHeight, infoWindowWidth, infoWindowWindowY, infoWindowWindowX);
    werase(infoWindow);

    draw_horizontal_line(infoWindow, infoWindowWidth); // draw upper wall

    wprintw(infoWindow, "<!              !>");
    wprintw(infoWindow, "<!              !>");
    wprintw(infoWindow, "<!     NEXT:    !>");
    wprintw(infoWindow, "<!              !>");
    wprintw(infoWindow, "<!              !>");

    const Falling nextFalling = gameBoard.get_next_falling();
    for (SizeType i = 0; i < 4; ++i)
    {
        wprintw(infoWindow, "<!    ");
        for (SizeType j = 0; j < 3; ++j)
        {
            const CellState currentState = nextFalling.get_raw_cell_state(i, j);
            const char character = currentState ? '#' : ' '; // print character in case no colors are available

            wattron(infoWindow, convert_state_to_color(currentState));
            wprintw(infoWindow, "%c%c", character, character); // print twice to make the form more square
            wattroff(infoWindow, convert_state_to_color(currentState));
        }
        wprintw(infoWindow, "    !>");
    }
    draw_horizontal_line(infoWindow, infoWindowWidth); // draw lower wall

    // render information window and controls info
    wprintw(infoWindow, "<!              !>");
    wprintw(infoWindow, "<! LEVEL:       !>");
    wprintw(infoWindow, "<! %12d !>", gameBoard.get_level());
    wprintw(infoWindow, "<!              !>");
    wprintw(infoWindow, "<! LINE CLEARS: !>");
    wprintw(infoWindow, "<! %12d !>", gameBoard.get_line_clears());
    wprintw(infoWindow, "<!              !>");
    draw_horizontal_line(infoWindow, infoWindowWidth); // draw lower wall
    wprintw(infoWindow, "<! MOVE:        !>");
    wprintw(infoWindow, "<!   ARROW KEYS !>");
    wprintw(infoWindow, "<! ROTATE:      !>");
    wprintw(infoWindow, "<!   R  AND  U  !>");
    wprintw(infoWindow, "<! QUIT:        !>");
    wprintw(infoWindow, "<!   Q          !>");
    draw_horizontal_line(infoWindow, infoWindowWidth); // draw lower wall
    wrefresh(infoWindow);

    return;
}

void render_game_over()
{
    clear();
    printw("\n");
    printw("\n");
    printw("\n");
    printw("         ==================== \n");
    printw("         =   GAME IS OVER   = \n");
    printw("         ==================== \n");
    printw("\n");
    refresh();
    napms(5000); // wait 5 seconds
}

void initialize_ncurses()
{
    initscr(); // initialize ncurses library
    cbreak(); // disable buffering of typed characters and get a character-at-a-time input
    noecho(); // suppress automatic echoing of typed characters
    nodelay(stdscr, true); // non-blocking getch calls
    keypad(stdscr, true); // capture special keystrokes
    start_color();

    initialize_colors();
}

void finalize_ncurses()
{
    endwin(); // restore terminal settings
}