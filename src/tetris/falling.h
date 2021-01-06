#ifndef FALLING_H_
#define FALLING_H_

#include "types.h"
#include "shapes.h"

/*
 * Represents a falling object in the game board.
 * All public operations refer to properties of the accordingly rotated shape.
 * The coordinates are used like matrix indices.
 */
class Falling
{
public:
    /*
     * Constructor.
     *
     * @param[in] upperLeftH The falling object's height coordinate in the game board.
     * @param[in] upperLeftW The falling object's width coordinate in the game board.
     * @param[in] shapeType The falling object's shape type.
     * @param[in] stateType The falling object's cell state for alive shape cells, i.e. a color representation.
     */
    Falling(const SizeType upperLeftH, const SizeType upperLeftW, const ShapeType shapeType, const CellState stateType = 0xFF);

    /*
     * Default destructor.
     */
    ~Falling() = default;

    /*
     * Returns the accordingly rotated falling shape's state on the game board. Input: game board coordinates.
     * @param[in] i game board row index
     * @param[in] j game board column index
     */
    CellState get_cell_state_on_board(const SizeType i, const SizeType j) const;

    /*
     * Returns the accordingly rotated falling shape's state in absolute coordinates starting in (0/0).
     * If i or j are not feasible, 0 is returned, even though these coordinates are outside of the shape's
     * memory representation.
     *
     * @param[in] row index
     * @param[in] j column index
     */
    CellState get_raw_cell_state(const SizeType i, const SizeType j) const;

    /*
     * Return row coordinate of upper left corner.
     */
    SizeType get_upper_left_h() const;

    /*
     * Return column coordinate of upper left corner.
     */
    SizeType get_upper_left_w() const;

    /*
     * Return row coordinate of lower right corner.
     */
    SizeType get_lower_right_h() const;

    /*
     * Return column coordinate of lower right corner.
     */
    SizeType get_lower_right_w() const;

    /*
     * Return height.
     */
    SizeType get_height() const;

    /*
     * return width.
     */
    SizeType get_width() const;

    /*
     * Moves the shape up by one unit.
     */
    void move_up();

    /*
     * Moves the shape left by one unit.
     */
    void move_left();

    /*
     * Moves the shape right by one unit.
     */
    void move_right();

    /*
     * Moves the shape down by one unit.
     */
    void move_down();

    /*
     * Rotates the shape clockwise by 90°.
     */
    void rotate_clockwise();

    /*
     * Rotates the shape counterclockwise by 90°.
     */
    void rotate_counterclockwise();

private:

    /*
     * Returns the cell state of the unrotated base shape.
     *
     * @param[in] i row index
     * @param[in] j column index
     */
    CellState get_original_shape_cell_state(const SizeType i, const SizeType j) const;

    /*
     * Similar to public method get_raw_cell_state(i, j), but does not provide out-of-bounds-access.
     * Handle with care! This function is necessary because the rotated height and width of the object do not
     * necessarily coincide with those of the base shape.
     *
     * @param[in] i row index
     * @param[in] j column index
     */
    CellState get_rotated_shape_data(const SizeType i, const SizeType j) const;

private:
    SizeType _upperLeftH{0};
    SizeType _upperLeftW{0};
    Shape _currentShape{SHAPE_O};
    CellState _stateType{0xFF};

    RotationType _rotationStatus{ROT_0};
};

#endif /* FALLING_H_ */
