#include "Planet.hpp"
#include "GlobalData.h"
#include "Player.hpp"
#include "ArrayManager.hpp"
#include "Gfx.h"
#include <stdio.h>
#include <stdlib.h>

static GsSprite planetSprite;

void PlanetInit(void)
{
    GfxSpriteFromFile("DATA\\SPRITES\\PLANET.TIM", &planetSprite);
}

Planet::Planet() : SpaceEntity(planetSprite), CompositeSpriteEntity(planetSprite),
    mMaxHealth(4000),
    mConsumptionSpeed(5),
    mConsumerAmount(0),
    mSpriteAmount(ARRAY_SIZE(mSpriteOffsets)),
    mSpriteOffsets
    {
        // d   u    v
        {128, 0, 0},
        {96, 128, 16},
        {64, 0, 158},
        {48, 64, 163},
        {32, 112, 169}
    },
    mFlicker(false),
    mProvidingSafety(false)
{
    setActive(true);
    mPosition = Vector2(Vector2(rand() % (300 - 10 + 1) + 10, rand() % (300 - 10 + 1) + 10));
    mRadius = fix16_from_int(mSpriteOffsets[0].d >> 1);
    mHealth = mMaxHealth;
}

Planet::Planet(const unsigned int health) : Planet()
{
    mHealth = health;
}

void Planet::Update(GlobalData& gData)
{
    mConsumerAmount = 0;
    mProvidingSafety = false;

    ArrayManager<Player>& players = gData.Players;

    for (size_t i = 0; i < players.count(); i++)
    {
        Player& player = *players.get(i);

        if (player.isActive())
        {
            if (isCollidingWith(player))
            {
                mProvidingSafety = true;
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
        else if (mHealth - healthThresholds[i] < 200)
        {
            if (mFlicker ^= true && mProvidingSafety)
            {
                mSpr.w = mSpr.h = mSpriteOffsets[i + 1].d;
                mSpr.u = mSpriteOffsets[i + 1].u;
                mSpr.v = mSpriteOffsets[i + 1].v;
                mRadius = fix16_from_int(mSpriteOffsets[i + 1].d >> 1);
            }
            else
            {
            }
        }
    }

    SpaceEntity::render(cam);
}
