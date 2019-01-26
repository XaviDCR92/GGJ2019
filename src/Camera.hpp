#pragma once

#include "Vector2.hpp"
#include "Player.hpp"
#include "ArrayManager.hpp"

class Camera
{
public:
    Camera();
    void Update(const ArrayManager<Player>& players);
    Vector2 getPosition(const Vector2& origPos) const;

private:
    Vector2 mPosition;

};
