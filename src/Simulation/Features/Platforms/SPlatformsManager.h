#ifndef SPLATFORMSSPAWNER_H
#define SPLATFORMSSPAWNER_H
#include "EPlatform.h"
#include "Math/Vector2.h"
#include "Simulation/ECS/System.h"


class SPlatformsManager: public ECS::System
{
public:
    SPlatformsManager();

    bool Update(float dt) override;

private:
    void SpawnBottomPlatforms();
    void SpawnPlatform(Vector2f centerPos);
    bool IsSpawnRequired();
    Vector2f DetermineSpawnPos();

    static void RemoveLastPlatform();
    bool IsLastPlatformRemovable();

private:
    Vector2f platformSize;
    Vector2f platformOriginOffset;

    float minSpawnDistance = 0;
    float maxSpawnDistance = 0;
};


#endif //SPLATFORMSSPAWNER_H
