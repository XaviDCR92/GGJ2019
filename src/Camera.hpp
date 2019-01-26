#pragma once

#include "Vector2.hpp"
#include "Player.hpp"
#include "ArrayManager.hpp"

class Player;

class Camera
{
public:
    Camera();
    void Update(const ArrayManager<Player>& players);

private:
    Vector2 mPosition;

};
