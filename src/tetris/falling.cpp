#include "falling.h"

// public

Falling::Falling(const SizeType upperLeftH, const SizeType upperLeftW, const ShapeType shapeType, const CellState stateType)
: _upperLeftH{upperLeftH},
_upperLeftW{upperLeftW},
_currentShape{shapeType},
_stateType{stateType}
{}

CellState Falling::get_cell_state_on_board(const SizeType i, const SizeType j) const
{
    // shift game board coordinates to absolute shape coordinate
    const int8_t i_shifted = i - _upperLeftH;
    const int8_t j_shifted = j - _upperLeftW;
    return get_raw_cell_state(i_shifted, j_shifted);
}

CellState Falling::get_raw_cell_state(const SizeType i, const SizeType j) const
{
    // Return cell state or 0, if coordinates are outside the shape
    return (0 <= i && i < get_height() && 0 <= j && j < get_width()) ? get_rotated_shape_data(i, j) : 0;
}

SizeType Falling::get_upper_left_h() const
{
    return _upperLeftH;
}

SizeType Falling::get_upper_left_w() const
{
    return _upperLeftW;
}

SizeType Falling::get_lower_right_h() const
{
    return _upperLeftH + get_height() - 1;
}

SizeType Falling::get_lower_right_w() const
{
    return _upperLeftW + get_width() - 1;
}


SizeType Falling::get_height() const
{
    // height changes according to current rotation status
    switch (_rotationStatus)
    {
        case ROT_0:
            return _currentShape.get_height();
            break;
        case ROT_90:
            return _currentShape.get_width();
            break;
        case ROT_180:
            return _currentShape.get_height();
            break;
        case ROT_270:
            return _currentShape.get_width();
            break;
    }
}

SizeType Falling::get_width() const
{
    // width changes according to current rotation status
    switch (_rotationStatus)
    {
        case ROT_0:
            return _currentShape.get_width();
            break;
        case ROT_90:
            return _currentShape.get_height();
            break;
        case ROT_180:
            return _currentShape.get_width();
            break;
        case ROT_270:
            return _currentShape.get_height();
            break;
    }
}

void Falling::move_up()
{
    // decrement, because coordinates are used like matrix indices
    --_upperLeftH;
}

void Falling::move_left()
{
    --_upperLeftW;
}

void Falling::move_right()
{
    ++_upperLeftW;
}

void Falling::move_down()
{
    // increment, because coordinates are used like matrix indices
    ++_upperLeftH;
}

void Falling::rotate_clockwise()
{
    ++_rotationStatus;
}

void Falling::rotate_counterclockwise()
{
    --_rotationStatus;
}

// private

CellState Falling::get_original_shape_cell_state(const SizeType i, const SizeType j) const
{
    // internal state type is returned if shape cell is active
    return _stateType*_currentShape(i,j);
}

CellState Falling::get_rotated_shape_data(const SizeType i, const SizeType j) const
{
    // coordinate transpositions. They are calculated using the fact that rotating a matrix by 90° clockwise
    // corresponds to transposing and taking the columns in reverse order
    switch (_rotationStatus)
    {
        case ROT_0:
            return get_original_shape_cell_state(i, j);
            break;
        case ROT_90:
            return get_original_shape_cell_state(_currentShape.get_height() - 1 - j, i);
            break;
        case ROT_180:
            return get_original_shape_cell_state(_currentShape.get_height() - 1 - i, _currentShape.get_width() - 1 - j);
            break;
        case ROT_270:
            return get_original_shape_cell_state(j, _currentShape.get_width() - 1 - i);
            break;
    }
}