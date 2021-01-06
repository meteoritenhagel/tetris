// public:

template<SizeType height, SizeType width>
GameBoard<height, width>::GameBoard()
{
    // make sure that even the first shape falling down is random
    generate_new_falling();
    generate_new_falling();
}

template<SizeType height, SizeType width>
uint8_t GameBoard<height, width>::get_level() const
{
    return _level;
}

template<SizeType height, SizeType width>
uint16_t GameBoard<height, width>::get_line_clears() const
{
    return _lineClears;
}

template<SizeType height, SizeType width>
uint8_t GameBoard<height, width>::get_update_cycle_threshold() const
{
    return static_cast<uint8_t>(59.0 * pow(0.8, get_level()) + 1);
}

template<SizeType height, SizeType width>
CellState GameBoard<height, width>::get_cell_state(const SizeType i, const SizeType j) const
{
    // The current game board cell's state is dependent on whether a falling shape or a landed state is present
    CellState state = ((get_landed_state(i, j) | get_falling_state(i, j)));
    return state;
}

template<SizeType height, SizeType width>
Falling GameBoard<height, width>::get_next_falling() const
{
    return _nextFalling;
}

template<SizeType height, SizeType width>
bool GameBoard<height, width>::is_game_over() const
{
    return _gameOver;
}

template<SizeType height, SizeType width>
void GameBoard<height, width>::move_left_if_valid()
{
    // Move and check if new position is valid. Otherwise, undo move.
    _currentFalling.move_left();
    if (!falling_has_valid_position())
    {
        _currentFalling.move_right();
    }
    return;
}

template<SizeType height, SizeType width>
void GameBoard<height, width>::move_right_if_valid()
{
    // Move and check if new position is valid. Otherwise, undo move.
    _currentFalling.move_right();
    if (!falling_has_valid_position())
    {
        _currentFalling.move_left();
    }
    return;
}

template<SizeType height, SizeType width>
void GameBoard<height, width>::move_down_if_valid()
{
    // Move and check if new position is valid. Otherwise, undo move.
    _currentFalling.move_down();
    if (!falling_has_valid_position())
    {
        _currentFalling.move_up();
    }
    return;
}

template<SizeType height, SizeType width>
void GameBoard<height, width>::rotate_clockwise_if_valid()
{
    // Rotates and check if new position is valid. Otherwise, undo rotation.
    _currentFalling.rotate_clockwise();
    if (!falling_has_valid_position())
    {
        _currentFalling.rotate_counterclockwise();
    }
    return;
}

template<SizeType height, SizeType width>
void GameBoard<height, width>::rotate_counterclockwise_if_valid()
{
    // Rotates and check if new position is valid. Otherwise, undo rotation.
    _currentFalling.rotate_counterclockwise();
    if (!falling_has_valid_position())
    {
        _currentFalling.rotate_clockwise();
    }
}

template<SizeType height, SizeType width>
void GameBoard<height, width>::update()
{
    // Adjust current level. After 10 cleared rows, the level increases by 1.
    _level = get_line_clears() / 10;

    // Move and check if new position is valid. Otherwise, undo move, settle and generate new falling shape.
    _currentFalling.move_down();
    if (!falling_has_valid_position())
    {
        _currentFalling.move_up();
        convert_falling_to_landed();
        generate_new_falling();
    }
    return;
}

// private:

template<SizeType height, SizeType width>
CellState GameBoard<height, width>::get_landed_state(const SizeType i, const SizeType j) const
{
    return (_landedBlocks[i * width + j]);
}

template<SizeType height, SizeType width>
CellState GameBoard<height, width>::get_falling_state(const SizeType i, const SizeType j) const
{
    return _currentFalling.get_cell_state_on_board(i, j);
}

template<SizeType height, SizeType width>
bool GameBoard<height, width>::falling_has_valid_position() const
{
    if (_currentFalling.get_upper_left_h() < 0 || _currentFalling.get_upper_left_w() < 0 // upper left corner is outside game board boundaries
        || _currentFalling.get_lower_right_h() >= height || _currentFalling.get_lower_right_w() >= width) // lower right corner is outside boundaries
    {
        return false;
    }
    else // boundaries are fine, hence check shape points
    {
        for (SizeType x = _currentFalling.get_upper_left_h(); x <= _currentFalling.get_lower_right_h(); ++x)
        {
            for (SizeType y = _currentFalling.get_upper_left_w(); y <= _currentFalling.get_lower_right_w(); ++y)
            {
                if (get_falling_state(x, y) != 0 && get_landed_state(x, y) != 0) // falling and landed shapes are overlapping
                {
                    return false;
                }
            }
        }
    }

    return true;
}

template<SizeType height, SizeType width>
void GameBoard<height, width>::set_landed_cell_state(const SizeType i, const SizeType j, const CellState cellState)
{
    _landedBlocks[i * width + j] = cellState;
    return;
}

template<SizeType height, SizeType width>
void GameBoard<height, width>::convert_falling_to_landed()
{
    for (SizeType h = _currentFalling.get_upper_left_h(); h <= _currentFalling.get_lower_right_h(); ++h)
    {
        for (SizeType w = _currentFalling.get_upper_left_w(); w <= _currentFalling.get_lower_right_w(); ++w)
        {
            set_landed_cell_state(h, w, get_cell_state(h, w)); // set falling shape to landed
            if (get_falling_state(h, w)) // increase number of active cells in row
            {
                ++_cellsInRow[h];
            }
        }

        if (_cellsInRow[h] == width) // clear row if necessary
        {
            clear_row(h);
        }
    }
    return;
}

template<SizeType height, SizeType width>
void GameBoard<height, width>::clear_row(const SizeType row)
{
    // shift all cells above the one to be deleted one down (or do nothing in case the uppermost row is full)
    std::move(_landedBlocks.begin(), _landedBlocks.begin() + row * width,
              _landedBlocks.begin() + width);
    // update number of active cells for the shifted rows
    std::move(_cellsInRow.begin(), _cellsInRow.begin() + row,
              _cellsInRow.begin() + 1);

    // the most upper row has 0 active cells now
    std::fill(_landedBlocks.begin(), _landedBlocks.begin() + width, 0);
    _cellsInRow[0] = 0;

    ++_lineClears; // increase number of cleared lines
    return;
}

template<SizeType height, SizeType width>
void GameBoard<height, width>::generate_new_falling()
{
    static const time_t seed = time(NULL); // generate static seed
    static std::default_random_engine generator(seed);
    static std::uniform_int_distribution<int> distribution(0,255); // uniform distribution for shape and cell state generation

    const int randomShapeNumber = distribution(generator);
    const int randomCellState = distribution(generator);

    ShapeType shape = static_cast<ShapeType>(randomShapeNumber % _SHAPE_COUNT);
    CellState stateType = randomCellState;

    // place previous _nextFalling shape on top of game board
    _currentFalling = _nextFalling;

    // create shape that is going to fall next
    Falling newFalling(0, (width - 1) / 2, shape, stateType);
    _nextFalling = newFalling;

    if (!falling_has_valid_position()) // if new falling shape overlaps with already fallen blocks, the game terminates
    {
        _gameOver = true;
    }
    return;
}