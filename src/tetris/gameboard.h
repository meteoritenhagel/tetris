#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_

#include "falling.h"

#include <iostream>
#include <random>

template<SizeType height, SizeType width>
class GameBoard
{
public:
    /*
     * Constructor.
     */
    GameBoard();

    /*
     * Destructor.
     */
    ~GameBoard() = default;

    /*
     * Returns the player's current level
     * @return current level
     */
    uint8_t get_level() const;

    /*
     * Returns the player's current level
     * @return current level
     */
    uint16_t get_line_clears() const;

    /*
     * Returns the current recommended update cycle threshold.
     * Please call update() after every get_update_cycle_threshold() frames
     *
     * Then, for the recommended frame rate of 60 Hz a threshold of 60 means that the falling shape should
     * be updated once a second.
     *
     * @return update cycle threshold
     */
    uint8_t get_update_cycle_threshold() const;

    /*
     * Returns the current cell state of a certain game board cell.
     * i and j must be such that 0 <= i < height
     *                           0 <= j < width
     * @return cell state of cell with coordinates (i,j)
     */
    CellState get_cell_state(const SizeType i, const SizeType j) const;

    /*
     * Returns the shape which is generated after the current falling shape has settled.
     * The shape can be used to display it as additional information for the player.
     *
     * @return next falling shape
     */
    Falling get_next_falling() const;

    /*
     * Check if game is already over, meaning that not enough space on the gameboard is available
     * for creating a new falling shape.
     * This value can be used to initiate a game over screen or similar.
     *
     * @return true if game is over
     */
    bool is_game_over() const;

    /*
     * Moves the currently falling shape one unit to the left if the new position is valid.
     * Otherwise, the position stays unchanged.
     */
    void move_left_if_valid();

    /*
     * Moves the currently falling shape one unit to the right if the new position is valid.
     * Otherwise, the position stays unchanged.
     */
    void move_right_if_valid();

    /*
     * Moves the currently falling shape one unit down if the new position is valid.
     * Otherwise, the position stays unchanged.
     */
    void move_down_if_valid();

    /*
    * Rotates the currently falling shape by 90° clockwise if the new position is valid.
    * Otherwise, the position stays unchanged.
    */
    void rotate_clockwise_if_valid();

    /*
    * Rotates the currently falling shape by 90° counterclockwise if the new position is valid.
    * Otherwise, the position stays unchanged.
    */
    void rotate_counterclockwise_if_valid();

    /*
     * Updates the game board.
     * 1. Adjusts the player's current level.
     * 2. Moves the falling shape down by one unit if the new position is valid.
     * 3. Otherwise, the shape settles and a new shape starts falling from above.
     */
    void update();

private:

    /*
     * Returns the current cell state of previously landed shapes.
     * @return cell state
     */
    CellState get_landed_state(const SizeType i, const SizeType j) const;

    /*
     * Returns the current cell state of the currently falling shape.
     * @return cell state
     */
    CellState get_falling_state(const SizeType i, const SizeType j) const;

    /*
     * Determines whether the falling shape is in a valid position,
     * meaning that it
     * 1. does not collide with any already landed blocks
     * 2. does not overlap the game board boundaries
     *
     * @return true if the position is valid
     */
    bool falling_has_valid_position() const;

    /*
     * Applies the cell state cellState to the cell with coordinates (i,j) in the array of landed cells.
     *
     * @param[in] i row index
     * @param[in] j column index
     * @param[in] cellState cell state to apply
     */
    void set_landed_cell_state(const SizeType i, const SizeType j, const CellState cellState);

    /*
     * 1. Converts the currently falling shape into a landed shape.
     * 2. Updates the number of currently active cells in row.
     * 3. Clears rows if necessary.
     */
    void convert_falling_to_landed();

    /*
     * Delete row.
     * @param[in] row index to delete
     */
    void clear_row(const SizeType row);

    /*
     * Next falling shape starts falling down.
     * A new random falling shape is generated with random cell state and is going to be the next shape
     * falling down after the currently falling shape has settled.
     */
    void generate_new_falling();

private:
    std::array<SizeType, height> _cellsInRow{ 0 }; ///< number of currently active cells in each row. Used for checking whether row is full.
    std::array<CellState, height * width> _landedBlocks{ 0 }; ///< the array of landed blocks
    Falling _currentFalling{0, (width - 1) / 2, SHAPE_L }; //< the currently falling shape
    Falling _nextFalling{0, (width - 1) / 2, SHAPE_L }; ///< the shape which is going to fall down after the currently falling shape has settled
    bool _gameOver{ false }; ///< indicating whether game is terminated
    uint8_t _level{ 0 }; ///< player's current level
    uint16_t _lineClears{ 0 }; ///< player's current number of cleared rows
};

#include "gameboard.hpp"
#endif /* GAMEBOARD_H_ */
