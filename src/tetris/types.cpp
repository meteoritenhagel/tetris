#include "types.h"

// public

RotationType::RotationType(const Rotation rotation)
        : _rotation(rotation)
{}

RotationType::operator Rotation() const {
    return _rotation;
}

RotationType& RotationType::operator++()
{
    _rotation = static_cast<Rotation>((_rotation + 1) % 4);
    return (*this);
}

RotationType& RotationType::operator--()
{
    // get positive module
    _rotation = static_cast<Rotation>((4 + (_rotation - 1) % 4) % 4);
    return (*this);
}

