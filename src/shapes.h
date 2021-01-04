#ifndef SHAPE_H
#define SHAPE_H

#include "types.h"

using CellState = uint8_t;
constexpr CellState CS_DEAD = 0;

using ShapePointer = SizeType const *;

enum ShapeType : uint8_t
{
    SHAPE_O,
    SHAPE_L,
    SHAPE_J,
    SHAPE_I,
    SHAPE_S,
    SHAPE_T,
    SHAPE_Z,
    _SHAPE_COUNT
};

class ShapeO
{
public:
    ShapeO() = default;
    SizeType const * data() const
    {
        return _representation.data();
    }
    constexpr static SizeType height{2};
    constexpr static SizeType width{2};
private:
    constexpr static std::array<SizeType, height*width> _representation{1,1,
                                                                        1,1};
};

class ShapeL
{
public:
    ShapeL() = default;
    SizeType const * data() const
    {
        return _representation.data();
    }
    constexpr static SizeType height{3};
    constexpr static SizeType width{2};
private:
    constexpr static std::array<SizeType, height*width> _representation{1,0,
                                                                        1,0,
                                                                        1,1};
};

class ShapeJ
{
public:
    ShapeJ() = default;
    SizeType const * data() const
    {
        return _representation.data();
    }
    constexpr static SizeType height{3};
    constexpr static SizeType width{2};
private:
    constexpr static std::array<SizeType, height*width> _representation{0,1,
                                                                        0,1,
                                                                        1,1};
};

class ShapeI
{
public:
    ShapeI() = default;
    SizeType const * data() const
    {
        return _shapeO.data();
    }
    constexpr static SizeType height{4};
    constexpr static SizeType width{1};
private:
    ShapeO _shapeO{};
};

class ShapeS
{
public:
    ShapeS() = default;
    SizeType const * data() const
    {
        return _representation.data();
    }
    constexpr static SizeType height{2};
    constexpr static SizeType width{3};
private:
    constexpr static std::array<SizeType, height*width> _representation{0,1,1,
                                                                        1,1,0};
};

class ShapeT
{
public:
    ShapeT() = default;
    SizeType const * data() const
    {
        return _representation.data();
    }
    constexpr static SizeType height{2};
    constexpr static SizeType width{3};
private:
    constexpr static std::array<SizeType, height*width> _representation{0,1,0,
                                                                        1,1,1};
};

class ShapeZ
{
public:
    ShapeZ() = default;
    SizeType const * data() const
    {
        return _representation.data();
    }
    constexpr static SizeType height{2};
    constexpr static SizeType width{3};
private:
    constexpr static std::array<SizeType, height*width> _representation{1,1,0,
                                                                        0,1,1};
};

class Shape
{
public:
    Shape (const ShapeType shapeType)
    {
        switch (shapeType)
        {
        case SHAPE_O:
            _shapePointer = shapeO.data();
            _height = shapeO.height;
            _width = shapeO.width;
            break;
        case SHAPE_L:
            _shapePointer = shapeL.data();
            _height = shapeL.height;
            _width = shapeL.width;
            break;
        case SHAPE_J:
            _shapePointer = shapeJ.data();
            _height = shapeJ.height;
            _width = shapeJ.width;
            break;
        case SHAPE_I:
            _shapePointer = shapeI.data();
            _height = shapeI.height;
            _width = shapeI.width;
            break;
        case SHAPE_S:
            _shapePointer = shapeS.data();
            _height = shapeS.height;
            _width = shapeS.width;
            break;
        case SHAPE_T:
            _shapePointer = shapeT.data();
            _height = shapeT.height;
            _width = shapeT.width;
            break;
        case SHAPE_Z:
        default:
            _shapePointer = shapeZ.data();
            _height = shapeZ.height;
            _width = shapeZ.width;
            break;
        }
    }

    CellState operator()(const SizeType i, const SizeType j) const
    {
        return _shapePointer[i*_width + j];
    }

    SizeType get_height() const
    {
        return _height;
    }

    SizeType get_width() const
    {
        return _width;
    }

private:
    ShapeType _shapeType;

    SizeType _height;
    SizeType _width;
    ShapePointer _shapePointer;

    ShapeO shapeO{};
    ShapeL shapeL{};
    ShapeJ shapeJ{};
    ShapeI shapeI{};
    ShapeS shapeS{};
    ShapeT shapeT{};
    ShapeZ shapeZ{};
};

#endif
