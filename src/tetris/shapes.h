#ifndef SHAPE_H
#define SHAPE_H

#include "types.h"

using CellState = uint8_t; ///< Defines the type of the cell state, i.e. representing color

using ShapePointer = SizeType const *;

/*
 * Enumeration of all shapes. The number of shapes is available via _SHAPE_COUNT.
 */
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

/*
 * O shape.
 */
class ShapeO
{
public:
    ShapeO() = default;

    /*
     * Returns a pointer to the shape's memory representation.
     */
    SizeType const * data() const;

    constexpr static SizeType height{2};
    constexpr static SizeType width{2};
private:
    constexpr static std::array<SizeType, height*width> _representation{1,1,
                                                                        1,1};
};

/*
 * L shape.
 */
class ShapeL
{
public:
    ShapeL() = default;

    /*
     * Returns a pointer to the shape's memory representation.
     */
    SizeType const * data() const;

    constexpr static SizeType height{3};
    constexpr static SizeType width{2};
private:
    constexpr static std::array<SizeType, height*width> _representation{1,0,
                                                                        1,0,
                                                                        1,1};
};

/*
 * J shape.
 */
class ShapeJ
{
public:
    ShapeJ() = default;

    /*
     * Returns a pointer to the shape's memory representation.
     */
    SizeType const * data() const;

    constexpr static SizeType height{3};
    constexpr static SizeType width{2};
private:
    constexpr static std::array<SizeType, height*width> _representation{0,1,
                                                                        0,1,
                                                                        1,1};
};

/*
 * I shape.
 */
class ShapeI
{
public:
    ShapeI() = default;

    /*
     * Returns a pointer to the shape's memory representation.
     */
    SizeType const * data() const;

    constexpr static SizeType height{4};
    constexpr static SizeType width{1};
private:
    ShapeO _shapeO{};
};

/*
 * S shape.
 */
class ShapeS
{
public:
    ShapeS() = default;

    /*
     * Returns a pointer to the shape's memory representation.
     */
    SizeType const * data() const;

    constexpr static SizeType height{2};
    constexpr static SizeType width{3};
private:
    constexpr static std::array<SizeType, height*width> _representation{0,1,1,
                                                                        1,1,0};
};

/*
 * T shape.
 */
class ShapeT
{
public:
    ShapeT() = default;

    /*
     * Returns a pointer to the shape's memory representation.
     */
    SizeType const * data() const;

    constexpr static SizeType height{2};
    constexpr static SizeType width{3};
private:
    constexpr static std::array<SizeType, height*width> _representation{0,1,0,
                                                                        1,1,1};
};

/*
 * Z shape.
 */
class ShapeZ
{
public:
    ShapeZ() = default;

    /*
     * Returns a pointer to the shape's memory representation.
     */
    SizeType const * data() const;

    constexpr static SizeType height{2};
    constexpr static SizeType width{3};
private:
    constexpr static std::array<SizeType, height*width> _representation{1,1,0,
                                                                        0,1,1};
};

/*
 * General shape class.
 * When constructed with a ShapeType, the class takes on the corresponding base shape's properties.
 * All base shapes are contained via composition.
 */
class Shape
{
public:
    /*
     * Constructor. Takes a ShapeType as input and copies its properties into the class.
     * @param[in] shapeType Type of the desired shape.
     */
    Shape (const ShapeType shapeType);

    /*
     * Access operator. Accesses the memory representation in the form of a _height*_width-matrix.
     * 0 represents an empty cell, and 1 represents an occupied cell.
     * Only access for 0 <= i < _height and
     *                 0 <= j < _width.
     * @param[in] i row index
     * @param[in] j column index
     */
    CellState operator()(const SizeType i, const SizeType j) const;

    /*
     * Returns the shape's height.
     */
    SizeType get_height() const;

    /*
     * Returns the shape's width.
     */
    SizeType get_width() const;

private:
    ShapeType _shapeType; ///< Shape type.

    SizeType _height; ///< Height of underlying base shape.
    SizeType _width; ///< Width of underlying base shape.
    ShapePointer _shapePointer; ///< Pointer to memory representation of underlying base shape.

    ShapeO shapeO{};
    ShapeL shapeL{};
    ShapeJ shapeJ{};
    ShapeI shapeI{};
    ShapeS shapeS{};
    ShapeT shapeT{};
    ShapeZ shapeZ{};
};

#endif
