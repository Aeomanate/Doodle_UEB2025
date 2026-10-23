#ifndef CONFIGSIMULATION_H
#define CONFIGSIMULATION_H

#include "3rd-party/Framework.h"
#include "Math/Vector2.h"

// ==========================================================================

struct ConfigKeys
{
    FRKey left;
    FRKey right;
    FRKey noop1;
    FRKey noop2;
    FRMouseButton fire;
};

// ==========================================================================

struct ConfigPlayerCannon
{
    int cooldownS;
    int projectileSpeedPxSec;
    int projectileMass;
};

struct ConfigPlayer
{
    float mass;
    float movingSpeedPxS;
    float jumpDurationSec;
    Vector2f fallVelocity;
    Vector2f startOffset; // Determines the jump height
    ConfigPlayerCannon cannon;
};

struct ConfigEnemies
{
    float spawnProbability;
};

// ==========================================================================

struct ConfigLevel
{
    std::string name;
};

struct ConfigLevels
{
    ConfigLevel level1;
};

// ==========================================================================

struct ConfigAbilities
{
    Vector2f jetpackSpeed; // Abs values
    float jetpackDurationS; // Must be the same with the animation duration
    float shieldDurationS; // Abs values
};

// ==========================================================================

struct ConfigSimulation
{
    float fps;

    ConfigKeys keys;
    ConfigLevels configLevels;
    ConfigPlayer player;
    ConfigEnemies enemies;
    ConfigAbilities abilities;
};

// ==========================================================================
// Factory functions for default initialization
// ==========================================================================

ConfigKeys getDefaultConfigKeys();
ConfigPlayerCannon getDefaultConfigPlayerCannon();
ConfigPlayer getDefaultConfigPlayer();
ConfigEnemies getDefaultConfigEnemies();
ConfigLevel getDefaultConfigLevel(const std::string& name = "level name");
ConfigLevels getDefaultConfigLevels();
ConfigAbilities getDefaultConfigAbilities();
ConfigSimulation getDefaultConfigSimulation();

#endif //CONFIGSIMULATION_H
