<<<<<<< HEAD
#pragma once

class Player;
class Enemy;
class Planet;
class Camera;
template<class T>
class ArrayManager;
=======
#include "ArrayManager.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Planet.hpp"
#include "CollectableSource.hpp"
>>>>>>> 35d44e679297229ea7c185e1fb3bc291926a4053

struct GlobalData
{
    ArrayManager<Player>& Players;
    ArrayManager<Enemy>& Enemies;
    ArrayManager<Planet>& Planets;
    ArrayManager<CollectableSource>& Resources;
    Camera& camera;
};
