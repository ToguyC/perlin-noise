#include "vec2.h"
#include <math.h>
#include <stdio.h>

/// Create a 2d vector.
/// @param x_ The first component.
/// @param y_ The second component.
/// @return The newly created vector.
vec2 vec2_create(double x_, double y_)
{
    vec2 res = {x_, y_};
    return res;
}

/// Create a zero 2d vector.
/// @return The newly created zero vector.
vec2 vec2_create_zero() { return vec2_create(0.0, 0.0); }

/// Add two vectors.
/// @param lhs The left operand.
/// @param rhs The right operand.
/// @return The sum in a new vector.
vec2 vec2_add(vec2 lhs, vec2 rhs)
{
    return vec2_create(lhs.x + rhs.x, lhs.y + rhs.y);
}

/// Substract two vectors.
/// @param lhs The left operand.
/// @param rhs The right operand.
/// @return The difference in a new vector.
vec2 vec2_sub(vec2 lhs, vec2 rhs)
{
    return vec2_create(lhs.x - rhs.x, lhs.y - rhs.y);
}

/// Multiply a vector by a scalar.
/// @param lhs The left operand, a vector.
/// @param scalar The right operand, a scalar.
/// @return The product in a new vector.
vec2 vec2_mul(vec2 lhs, double scalar)
{
    return vec2_create(lhs.x * scalar, lhs.y * scalar);
}

/// Divide a vector by a scalar.
/// @param lhs The left operand, a vector.
/// @param scalar The right operand, a scalar.
/// @return The quotien in a new vector.
vec2 vec2_div(vec2 lhs, double scalar)
{
    return vec2_create(lhs.x / scalar, lhs.y / scalar);
}

/// Compute the dot product (scalar product) between two vectors.
/// @param lhs The left operand.
/// @param rhs The right operand.
/// @return The dot product.
double vec2_dot(vec2 lhs, vec2 rhs)
{
    return (lhs.x * rhs.x) + (lhs.y * rhs.y);
}

/// Compute the square of the euclidean norm of a given vector.
/// @param v The vector.
/// @return The square of the norm.
double vec2_norm_sqr(vec2 v) { return pow(v.x, 2) + pow(v.y, 2); }

/// Compute the euclidean norm of a given vector.
/// @param v The vector.
/// @return The norm.
double vec2_norm(vec2 v) { return sqrt(pow(v.x, 2) + pow(v.y, 2)); }

/// Compute the normalization of a given vector.
/// @param v The vector.
/// @return The new normalized vector.
vec2 vec2_normalize(vec2 v)
{
    return vec2_create(v.x / vec2_norm(v), v.y / vec2_norm(v));
}

/// Check whether two vectors are approximately equals within a given
/// tolerance.
/// @param lhs The left operand.
/// @param rhs The right operand.
/// @param eps The tolerance.
/// @return true if vector are approximately equal, false otherwise.
bool vec2_is_approx_equal(vec2 lhs, vec2 rhs, double eps)
{
    double diff = fabs(vec2_norm(lhs) - vec2_norm(rhs));
    return diff <= eps;
}

/// Compute the coordinates of a 2d vector (with components between 0 and 1)
/// in a given screen matrix.
/// @param v The 2d vector.
/// @param width The screen width.
/// @param height The screen height.
/// @return The coordinates (rwo, column).
coordinates vec2_to_coordinates(vec2 v, uint32_t width, uint32_t height)
{
    width--;
    height--;
    coordinates coord = {.row = floor((height / 2.0) + (v.y * (height / 2.0))),
                         .column =
                             floor((width / 2.0) + (v.x * (width / 2.0)))};
    return coord;
}

/// Print a vector in the standard output.
/// @param v The vector.
void vec2_print(vec2 v) { printf("x = %g, y = %g\n", v.x, v.y); }
