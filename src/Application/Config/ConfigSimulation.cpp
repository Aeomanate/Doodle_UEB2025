#include "ConfigSimulation.h"

ConfigKeys getDefaultConfigKeys()
{
    return ConfigKeys{
        .left = FRKey::LEFT,
        .right = FRKey::RIGHT,
        .noop1 = FRKey::UP,
        .noop2 = FRKey::DOWN,
        .fire = FRMouseButton::LEFT
    };
}

ConfigPlayerCannon getDefaultConfigPlayerCannon()
{
    return ConfigPlayerCannon{
        .cooldownS = 1000,
        .projectileSpeedPxSec = 300,
        .projectileMass = 1
    };
}

ConfigPlayer getDefaultConfigPlayer()
{
    return ConfigPlayer{
        .mass = 1,
        .movingSpeedPxS = 20,
        .jumpDurationSec = 5,
        .fallVelocity = { 0, 10 },
        .startOffset = { 0.5, 0.5 },
        .cannon = getDefaultConfigPlayerCannon()
    };
}

ConfigEnemies getDefaultConfigEnemies()
{
    return ConfigEnemies{
        .spawnProbability = 0.5
    };
}

ConfigLevel getDefaultConfigLevel(const std::string& name)
{
    return ConfigLevel{ .name = name };
}

ConfigLevels getDefaultConfigLevels()
{
    return ConfigLevels{
        .level1 = getDefaultConfigLevel("Endless")
    };
}

ConfigAbilities getDefaultConfigAbilities()
{
    return ConfigAbilities{
        .jetpackSpeed = { 0, 20 },
        .jetpackDurationS = 10,
        .shieldDurationS = 3
    };
}

ConfigSimulation getDefaultConfigSimulation()
{
    return ConfigSimulation{
        .fps = 59,
        .keys = getDefaultConfigKeys(),
        .configLevels = getDefaultConfigLevels(),
        .player = getDefaultConfigPlayer(),
        .enemies = getDefaultConfigEnemies(),
        .abilities = getDefaultConfigAbilities()
    };
}
