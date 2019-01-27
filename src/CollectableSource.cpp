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
    mStacks(3),
    mSpriteAmount(ARRAY_SIZE(mSpriteOffsets)),
    mCollectionCounter(150),
    mCurrentCollectionCounter(0),
    mFlickerCountStart(20),
    mFlicker(false),
    mSpriteOffsets
    {
        {48, 32, 0},
        {32, 80, 0},
        {16, 80, 32}
    }
{
    setActive(true);
    mPosition = Vector2(100, 100);
}

void CollectableSource::config(const Vector2& pos)
{
    mPosition = pos;
}

void CollectableSource::Update(GlobalData& gData)
{
    ArrayManager<Player>& players = gData.Players;
    bool being_gathered = false;

    for (size_t i = 0; i < players.count(); i++)
    {
        Player& player = *players.get(i);

        if(player.isActive())
        {
            if(isCollidingWith(player) && !player.isFull())
            {
                being_gathered = true;
                if(mCurrentCollectionCounter > 0)
                    mCurrentCollectionCounter--;
                else
                {
                    player.setCollected(true);
                    mCurrentCollectionCounter = mCollectionCounter;
                    mStacks--;
                    if(mStacks <= 0)
                        setActive(false);
                    break;
                }
            }
        }
    }

    if(!being_gathered && mCurrentCollectionCounter < mFlickerCountStart)
        mCurrentCollectionCounter = mFlickerCountStart;
}
void CollectableSource::render(const Camera& cam)
{
    const size_t size = ARRAY_SIZE(mSpriteOffsets);
    size_t idx = size - mStacks;

    size_t radius_idx = idx;
    if ((mFlicker ^= true) && mCurrentCollectionCounter < mFlickerCountStart)
        idx++;

    if(idx >= size)
        return;

    mSpr.w = mSpr.h = mSpriteOffsets[idx].d;
    mSpr.u = mSpriteOffsets[idx].u;
    mSpr.v = mSpriteOffsets[idx].v;
    mRadius = fix16_from_int(mSpriteOffsets[radius_idx].d >> 1);

    SpaceEntity::render(cam);
}
