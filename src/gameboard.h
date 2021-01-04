#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_

#include "falling.h"

#include <iostream>

template<SizeType height = 24, SizeType width = 10>
class GameBoard
{
public:
    GameBoard()
    {
    }

    // TODO: REMOVE private
    //private:
    std::array<SizeType, height> _cellsInRow
    { 0 };
    std::array<CellState, height * width> _landedBlocks
    { 0 };
    Falling _falling
    { 0, (width - 1) / 2, SHAPE_L };

    void delete_row(const SizeType row)
    {
        std::move(_landedBlocks.begin(), _landedBlocks.begin() + row * width,
                _landedBlocks.begin() + width);
        std::move(_cellsInRow.begin(), _cellsInRow.begin() + row,
                _cellsInRow.begin() + 1);
        std::fill(_landedBlocks.begin(), _landedBlocks.begin() + width, 0);
        _cellsInRow[0] = 0;
        return;
    }

    void set_cell_state(const SizeType i, const SizeType j,
            const CellState cellState)
    {
        _landedBlocks[i * width + j] = cellState;
        return;
    }

    CellState get_landed_state(const SizeType i, const SizeType j) const
    {
        return (_landedBlocks[i * width + j]);
    }

    CellState get_falling_state(const SizeType i, const SizeType j) const
    {
        return _falling.get_cell_state(i, j);
    }

    CellState get_cell_state(const SizeType i, const SizeType j) const
    {
        CellState state = ((get_landed_state(i, j) | get_falling_state(i, j)));
        return state;
    }

    bool falling_has_valid_position() const
    {
        if (_falling.get_upper_left_h() < 0 || _falling.get_upper_left_w() < 0
                || _falling.get_lower_right_h() >= height
                || _falling.get_lower_right_w() >= width)
        {
            return false;
        }
        else
        {
            for (SizeType x = _falling.get_upper_left_h();
                    x <= _falling.get_lower_right_h(); ++x)
            {
                for (SizeType y = _falling.get_upper_left_w();
                        y <= _falling.get_lower_right_w(); ++y)
                {
                    if (get_falling_state(x, y) != CS_DEAD
                            && get_landed_state(x, y) != CS_DEAD)
                    {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    void move_left_if_valid()
    {
        _falling.move_left();
        if (!falling_has_valid_position())
        {
            _falling.move_right();
        }
        return;
    }

    void move_right_if_valid()
    {
        _falling.move_right();
        if (!falling_has_valid_position())
        {
            _falling.move_left();
        }
        return;
    }

    void move_down_if_valid()
    {
        _falling.move_down();
        if (!falling_has_valid_position())
        {
            _falling.move_up();
        }
        return;
    }

    void rotate_if_valid()
    {
        _falling.rotate();
        if (!falling_has_valid_position())
        {
            _falling.unrotate();
        }
    }

    void convert_falling_to_landed()
    {
        for (SizeType h = _falling.get_upper_left_h();
                h <= _falling.get_lower_right_h(); ++h)
        {
            for (SizeType w = _falling.get_upper_left_w();
                    w <= _falling.get_lower_right_w(); ++w)
            {
                set_cell_state(h, w, get_cell_state(h, w));
                if (get_falling_state(h, w))
                {
                    ++_cellsInRow[h];
                }
            }

            if (_cellsInRow[h] == width)
            {
                delete_row(h);
            }
        }
        return;
    }

    void generate_new_falling()
    {
        ShapeType shape = static_cast<ShapeType>(rand() % _SHAPE_COUNT);
        CellState stateType = rand();

        Falling falling(0, (width - 1) / 2, shape, stateType);
        _falling = falling;

        if (!falling_has_valid_position())
        {
            game_over();
        }
        return;
    }

    void update()
    {
        _falling.move_down();
        if (!falling_has_valid_position())
        {
            _falling.move_up();
            convert_falling_to_landed();
            generate_new_falling();
        }
        return;
    }

    void game_over()
    {
        std::cout << "          -------------------" << '\n'
                << "          ---- GAME OVER ----" << '\n'
                << "          -------------------" << '\n';
        exit(0);
    }

    uint8_t get_update_cycle_threshold() const
    {
        return 60;
    }
};

#endif /* GAMEBOARD_H_ */
