#pragma once

#include "Vector2.hpp"

class Camera
{
public:
    Camera();
    void Update(const Vector2& p1, const Vector2& p2);
    void getPosition(int& x, int& y) const;

private:
    Vector2 mPosition;

};
