#include "ArrayManager.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Planet.hpp"
#include "CollectableSource.hpp"

struct GlobalData
{
    ArrayManager<Player>& Players;
    ArrayManager<Enemy>& Enemies;
    ArrayManager<Planet>& Planets;
    ArrayManager<CollectableSource>& Resources;
    Camera& camera;
};
