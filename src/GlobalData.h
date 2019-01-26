#pragma once

class Player;
class Enemy;
class Planet;
class Camera;
template<class T>
class ArrayManager;

struct GlobalData
{
    ArrayManager<Player>& Players;
    ArrayManager<Enemy>& Enemies;
    ArrayManager<Planet>& Planets;
    Camera& camera;
};
