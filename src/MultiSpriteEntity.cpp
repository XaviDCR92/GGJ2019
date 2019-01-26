#include "MultiSpriteEntity.hpp"

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