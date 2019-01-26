#include "MultiSpriteEntity.hpp"

void CompositeSpriteEntity::SetSpriteOriginOnce(unsigned char startU, unsigned char startV)
{
    if(mOriginSet)
        return;

    SetSpriteOrigin(mStartU, mStartV);
}

void CompositeSpriteEntity::SetSpriteOrigin(unsigned char startU, unsigned char startV) 
{
    mStartU = startU;
    mStartV = startV;
    mOriginSet = true;
}

void CompositeSpriteEntity::GetSpriteOrigin(unsigned char& startU, unsigned char& startV) const
{
    startU = mStartU;
    startV = mStartV;
}