#include "Vector2.hpp"

Vector2::Vector2()
{
    X = Y = 0;
}

Vector2::Vector2(int initialX, int initialY)
{
    X = Fix16(initialX);
    Y = Fix16(initialY);
}

Vector2::Vector2(Fix16 initialX, Fix16 initialY)
{
    X = initialX;
    Y = initialY;
}

Fix16 Vector2::Distance()
{
    return fix16_sqrt(DistanceSqr());
}

Fix16 Vector2::DistanceSqr()
{
    return X*X + Y*Y;
}

Vector2 Vector2::operator+=(const Vector2& rhs)
{
    X = X+rhs.X;
    Y = Y+rhs.Y;
    return *this;
}

Vector2 Vector2::operator+(const Vector2& rhs)
{
    return Vector2(X+rhs.X, Y+rhs.Y);
}

Vector2 Vector2::operator-(const Vector2& rhs)
{
    return Vector2(X-rhs.X, Y - rhs.Y);
}

Vector2 Vector2::operator-=(const Vector2& rhs)
{
    X = X - rhs.X;
    Y = Y - rhs.Y;
    return *this;
}

Vector2 Vector2::operator*(const Fix16& rhs)
{
    return Vector2(X * rhs, Y * rhs);
}