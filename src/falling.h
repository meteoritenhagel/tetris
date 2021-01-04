/*
 * falling.h
 *
 *  Created on: Nov 14, 2020
 *      Author: tristan
 */

#ifndef FALLING_H_
#define FALLING_H_

#include "types.h"
#include "shapes.h"

class Falling
{
public:
	Falling(const SizeType upperLeftH, const SizeType upperLeftW, const ShapeType shapeType, const CellState stateType = 0xFF)
	: _upperLeftH{upperLeftH},
	  _upperLeftW{upperLeftW},
	  _currentShape{shapeType},
	  _stateType{stateType}
	{}

	Falling(const Falling&) = default;
	Falling(Falling&&) = default;

	Falling& operator=(const Falling&) = default;
	Falling& operator=(Falling&&) = default;

	void move_up()
	{
		--_upperLeftH;
	}

	void move_left()
	{
		--_upperLeftW;
	}

	void move_right()
	{
		++_upperLeftW;
	}

	void move_down()
	{
		++_upperLeftH;
	}

	void rotate()
	{
		++_rotationStatus;
	}

	void unrotate()
	{
		--_rotationStatus;
	}

	SizeType get_rotated_height() const
	{
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

	SizeType get_rotated_width() const
	{
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

	CellState access_original_shape(const SizeType i, const SizeType j) const
	{
		return _stateType*_currentShape(i,j);
	}

	CellState get_rotated_shape_data(const SizeType i, const SizeType j) const
	{
		switch (_rotationStatus)
		{
		case ROT_0:
			return access_original_shape(i, j);
			break;
		case ROT_90:
			return access_original_shape(_currentShape.get_height()-1-j, i);
			break;
		case ROT_180:
			return access_original_shape(_currentShape.get_height()-1-i, _currentShape.get_width()-1-j);
			break;
		case ROT_270:
			return access_original_shape(j, _currentShape.get_width()-1-i);
			break;
		}
	}

	CellState get_cell_state(const SizeType i, const SizeType j) const
	{
		const int8_t i_shifted = i - _upperLeftH;
		const int8_t j_shifted = j - _upperLeftW;
		return (0 <= i_shifted && i_shifted < get_rotated_height() && 0 <= j_shifted && j_shifted < get_rotated_width()) ? get_rotated_shape_data(i_shifted, j_shifted) : 0;
	}

	SizeType get_upper_left_h() const
	{
		return _upperLeftH;
	}

	SizeType get_upper_left_w() const
	{
		return _upperLeftW;
	}

	SizeType get_lower_right_h() const
	{
		return _upperLeftH + get_rotated_height() - 1;
	}

	SizeType get_lower_right_w() const
	{
		return _upperLeftW + get_rotated_width() - 1;
	}

//TODO
//private:
	SizeType _upperLeftH{0};
	SizeType _upperLeftW{0};
	Shape _currentShape{SHAPE_O};
	CellState _stateType{0xFF};

	RotationType _rotationStatus{ROT_0};
};

#endif /* FALLING_H_ */
