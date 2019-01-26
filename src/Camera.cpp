#include "Camera.hpp"
#include "Gfx.h"
#include <stdio.h>
#include <stdlib.h>

Camera::Camera() :
    mPosition(Vector2(0, 0))
{
}

void Camera::Update(const Vector2& p1, const Vector2& p2)
{
    mPosition.X.value = abs(p1.X.value - p2.X.value) / 2;
    mPosition.Y.value = abs(p1.Y.value - p2.Y.value) / 2;

    printf( "Camera pos:\n"
            "\tX = %d\n"
            "\tY = %d\n",
            mPosition.X.value,
            mPosition.Y.value);
}

void Camera::getPosition(int& x, int& y) const
{
    x = (X_SCREEN_RESOLUTION >> 1) - fix16_to_int(mPosition.X.value);
    y = (Y_SCREEN_RESOLUTION >> 1) - fix16_to_int(mPosition.Y.value);
}
