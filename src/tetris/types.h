#ifndef TYPES_H_
#define TYPES_H_

#include <array>
#include <cstdlib>
#include <iostream>

using SizeType = int8_t; ///< Size type for game board dimensions and coordinates

/*
 * Enumeration of rotations.
 */
enum Rotation : uint8_t
{
    ROT_0,
    ROT_90,
    ROT_180,
    ROT_270
};

/*
 * Rotation class. Saves its current rotation.
 */
class RotationType
{
public:
    /*
     * Constructor.
     * Initializes the RotationType object with a given rotation.
     */
    RotationType(const Rotation rotation);

    ~RotationType() = default;

    /*
     * Implicit conversion operator to type Rotation.
     */
    operator Rotation() const;

    /*
     * Increment operator.
     * Corresponds to rotating the current RotationType object 90° clockwise.
     */
    RotationType& operator++();

   /*
    * Decrement operator.
    * Corresponds to rotating the current RotationType object 90° counterclockwise.
    */
    RotationType& operator--();

private:
    Rotation _rotation; ///< The current rotation status.
};

#endif /* TYPES_H_ */
