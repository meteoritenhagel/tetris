#include "shapes.h"

SizeType const * ShapeO::data() const
{
    return _representation.data();
}

SizeType const * ShapeL::data() const
{
    return _representation.data();
}

SizeType const * ShapeJ::data() const
{
    return _representation.data();
}

SizeType const * ShapeI::data() const
{
    return _shapeO.data();
}

SizeType const * ShapeS::data() const
{
    return _representation.data();
}

SizeType const * ShapeT::data() const
{
    return _representation.data();
}

SizeType const * ShapeZ::data() const
{
    return _representation.data();
}

Shape::Shape (const ShapeType shapeType)
{
    // copy the pointer to the base shape's memory representation and other properties into the class
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

CellState Shape::operator()(const SizeType i, const SizeType j) const
{
    return _shapePointer[i*_width + j];
}

SizeType Shape::get_height() const
{
    return _height;
}

SizeType Shape::get_width() const
{
    return _width;
}