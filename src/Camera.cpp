#include "Camera.hpp"
#include "Player.hpp"
#include "ArrayManager.hpp"

Camera::Camera() :
    mPosition(Vector2(0, 0))
{
}

void Camera::Update(const ArrayManager<Player>& players)
{
    mPosition = Vector2(0, 0);

    for (size_t i = 0; i < players.count(); i++)
    {
        const Player& player = *players.get(i);

        if (player.isActive())
        {
            mPosition += player.getPosition();
        }
    }

    mPosition /= Fix16(2);
}

Vector2 Camera::getPosition(const Vector2& origPos)
{
    return Vector2(mPosition - origPos);
}
