#include "Planet.hpp"

class Earth : public Planet
{
public:

    Earth();
    virtual void Update(GlobalData& data) override;
    virtual void render(const Camera& cam) override;
    void DumpResources(int amount);

private:

    GsSprite& mEarthSpr;
    int mHealthPerResource;

};

void EarthInit();