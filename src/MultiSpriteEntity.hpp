#pragma once

class CompositeSpriteEntity
{
public:

    CompositeSpriteEntity() : mOriginSet(false)
    {}

    void SetSpriteOriginOnce(unsigned char startU, unsigned char startV);
    void SetSpriteOrigin(unsigned char startU, unsigned char startV);
    void GetSpriteOrigin(unsigned char& startU, unsigned char& startV) const;

private:

    bool mOriginSet;
    unsigned char mStartU, mStartV;
};