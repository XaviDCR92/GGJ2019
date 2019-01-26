#pragma once

#include <fixmath.h>

class Vector2
{
public:

    Vector2();
    Vector2(int initialX, int initialY);
    Vector2(Fix16 initialX, Fix16 initialY);

    Fix16 Distance();
    Fix16 DistanceSqr();

    Vector2 operator+=(const Vector2& rhs);
    Vector2 operator+(const Vector2& rhs);
    Vector2 operator-(const Vector2& rhs);
    Vector2 operator-=(const Vector2& rhs);
    Vector2 operator*(const Fix16& rhs);

    Fix16 X, Y;

};