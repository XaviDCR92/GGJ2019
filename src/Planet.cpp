#include "Planet.hpp"
#include "GlobalData.h"
#include "Player.hpp"
#include "ArrayManager.hpp"
#include "Gfx.h"

Planet::Planet(GsSprite& spr, const Camera& cam) : SpaceEntity(spr), CompositeSpriteEntity(spr),
    mConsumerAmount(0),
    mHealth(4000),
    mConsumptionSpeed(5),
    mMaxHealth(4000),
    mSpriteAmount(ARRAY_SIZE(mSpriteOffsets)),
    mSpriteOffsets
    {
        // d   u    v
        {128, 0, 0},
        {96, 128, 16},
        {64, 0, 158},
        {48, 64, 163},
        {32, 112, 169}
    }
{
    setActive(true);
    mPosition = Vector2(210, 200);
    mRadius = fix16_from_int(mSpriteOffsets[0].d >> 1);
}

void Planet::Update(GlobalData& gData)
{
    mConsumerAmount = 0;

    ArrayManager<Player>& players = gData.Players;

    for (size_t i = 0; i < players.count(); i++)
    {
        Player& player = *players.get(i);

        if (player.isActive())
        {
            if (IsColliding(player, gData.camera))
            {
                player.setUnderCover(true);
                mConsumerAmount++;
            }
            else
            {
                player.setUnderCover(false);
            }
        }
    }

    const unsigned int mDiff = mConsumerAmount * mConsumptionSpeed;

    if (mHealth >= mDiff)
    {
        mHealth -= mDiff;
    }
    else
    {
        mHealth = 0;
    }

    if (mHealth <= 0)
        setActive(false);
}

void Planet::render(const Camera& cam)
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
