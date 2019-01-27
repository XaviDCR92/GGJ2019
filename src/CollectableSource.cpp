#include "CollectableSource.hpp"
#include "GlobalData.h"
#include "ArrayManager.hpp"
#include "Player.hpp"
#include "Gfx.h"

static GsSprite resourceSprite;

void ResourcesInit(void)
{
    GfxSpriteFromFile("DATA\\SPRITES\\RESOURCE.TIM", &resourceSprite);
}

CollectableSource::CollectableSource():
    SpaceEntity(resourceSprite), CompositeSpriteEntity(resourceSprite),
    mHealth(4000),
    mConsumptionSpeed(5),
    mMaxHealth(4000),
    mSpriteAmount(ARRAY_SIZE(mSpriteOffsets)),
    mCollectionCounter(50),
    mCurrentCollectionCounter(0),
    mSpriteOffsets
    {
        {64, 48, 32},
        {64, 48, 32},
        {64, 48, 32},
        {64, 48, 32},
        {64, 48, 32}
    }
{
    setActive(true);
    mPosition = Vector2(100, 100);
}

void CollectableSource::Update(GlobalData& gData)
{
    ArrayManager<Player>& players = gData.Players;
    //if(mCu)

    for (size_t i = 0; i < players.count(); i++)
    {
        Player& player = *players.get(i);

        if(player.isActive())
        {
            if(isCollidingWith(player))
            {
                if (mHealth >= mConsumptionSpeed)
                {
                    mHealth -= mConsumptionSpeed;
                }
                else
                {
                    mHealth = 0;
                }

                if (!mHealth)
                {
                    // Player needs get resources here
                    player.setCollected(true);

                    break;
                }
            }
        }
    }
}
void CollectableSource::render(const Camera& cam)
{
    static unsigned int healthThresholds[ARRAY_SIZE(mSpriteOffsets) - 1] =
    {
        3000,
        2000,
        1000,
        500,
    };

    mSpr.w = mSpr.h = mSpriteOffsets[0].d;
    mSpr.u = mSpriteOffsets[0].u;
    mSpr.v = mSpriteOffsets[0].v;
    mRadius = fix16_from_int(mSpriteOffsets[0].d >> 1);

    for (size_t i = 0; i < ARRAY_SIZE(healthThresholds); i++)
    {
        if (mHealth < healthThresholds[i])
        {
            mSpr.w = mSpr.h = mSpriteOffsets[i + 1].d;
            mSpr.u = mSpriteOffsets[i + 1].u;
            mSpr.v = mSpriteOffsets[i + 1].v;
            mRadius = fix16_from_int(mSpriteOffsets[i + 1].d >> 1);
        }
    }

    SpaceEntity::render(cam);
}
