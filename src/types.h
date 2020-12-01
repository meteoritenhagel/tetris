/*
 * types.h
 *
 *  Created on: Nov 14, 2020
 *      Author: tristan
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <array>
#include <cstdlib>
#include <iostream>

using SizeType = int8_t;

//constexpr std::array<uint32_t, 5> COLOUR_TABLE {0x00333333, 0x0060D634, 0x00C90B0B, 0x00E0E019, 0x0019E0D7};

enum Rotation : uint8_t
{
	ROT_0,
	ROT_90,
	ROT_180,
	ROT_270
};

class RotationType
{
public:
	RotationType(const Rotation rotation)
	: _rotation(rotation)
	{}

	operator Rotation() const
	{
		return _rotation;
	}

	RotationType& operator++()
	{
		_rotation = static_cast<Rotation>((_rotation + 1) % 4);
		return (*this);
	}

	RotationType& operator--()
	{
		// get positive module
		_rotation = static_cast<Rotation>((4 + (_rotation - 1) % 4) % 4);
		return (*this);
	}
private:
	Rotation _rotation;
};

void reset_lines(const SizeType numberOfLines)
{
	for (int i = 0; i < numberOfLines; ++i)
		std::cout << "\033[F" << "\33[2K";
	return;
}

#endif /* TYPES_H_ */
