#include "Arraymanager.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Planet.hpp"

struct GlobalData
{
    ArrayManager<Player>* Players;
    ArrayManager<Enemy>* Enemies;
    ArrayManager<Planet>* Planets;
};