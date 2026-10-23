#ifndef SENEMYSPAWNER_H
#define SENEMYSPAWNER_H
#include "Math/Vector2.h"
#include "Simulation/ECS/Entity.h"
#include "Simulation/ECS/System.h"


class SEnemyManager: public ECS::System
{
public:
    SEnemyManager();

    bool Update(float dt) override;

    void RemoveEnemy(ECS::Entity* pos);

    bool IsLastEnemyRemovable();

    void ProcessKilledEnemy();

private:
    std::vector<ECS::Entity*> enemies;

    Vector2f enemySize;
};


#endif //SENEMYSPAWNER_H
