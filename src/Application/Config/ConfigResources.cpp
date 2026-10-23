#include "ConfigResources.h"

ConfigTexture getDefaultConfigTexture(const fs::path& path, const Vector2f& scale, const Vector2f& originOffset)
{
    return ConfigTexture{
        .path = path,
        .scale = scale,
        .originOffset = originOffset
    };
}

ConfigCharacterTexture getDefaultConfigPlayerTexture()
{
    return ConfigCharacterTexture{
        .path = "player",
        .scale = { 0.7, 0.7 },
        .originOffset = { 0.5, 1 },
        .left = { .path = "Left.png", .scale = {1, 1}, .originOffset = {0.5, 1} },
        .right = { .path = "Right.png", .scale = {1, 1}, .originOffset = {0.5, 1} },
        .idle = { .path = "Idle.png", .scale = {1, 1}, .originOffset = {0.5, 1} }
    };
}

ConfigCharacterTexture getDefaultConfigEnemyTexture()
{
    return ConfigCharacterTexture{
        .path = "enemy",
        .scale = { 0.7, 0.7 },
        .originOffset = { 0.5, 1 },
        .left =  { .path = "doodlestein-left.png", .scale = {1, 1}, .originOffset = {0.5, 1} },
        .right = { .path = "doodlestein-right.png", .scale = {1, 1}, .originOffset = {0.5, 1} },
        .idle = { .path = "doodlestein-idle.png", .scale = {1, 1}, .originOffset = {0.5, 1} },
    };
}

ConfigAnimation getDefaultConfigJetpackAnimation()
{
    return ConfigAnimation{
        .path = "jetpack",
        .scale = { 0.7, 0.7 },
        .originOffset = { 0.5, 0.5 },
        .durationS = 10,
        .frameIntervalMs = 200,
        .startFrames = { 1, 2, 3 },
        .repeatFrames = { 4, 5, 6 },
        .finishFrames = { 7, 8, 9 },
        .idleFrames = { 10 }
    };
}

ConfigAnimation getDefaultConfigShieldAnimation()
{
    return ConfigAnimation{
        .path = "shield",
        .scale = { 1, 1 },
        .originOffset = { 0.5, 0.5 },
        .durationS = 10,
        .frameIntervalMs = 3333,
        .repeatFrames = { 1, 2, 3 }
    };
}

ConfigAnimation getDefaultConfigPlatformAnimation()
{
    return ConfigAnimation{
        .path = "platform",
        .scale = { 0.8, 0.7 },
        .originOffset = { 0.5, 1 },
        .durationS = 3,
        .frameIntervalMs = 600,
        .repeatFrames = { 2, 3, 4, 5 },
        .idleFrames = { 1 }
    };
}

ConfigTexture getDefaultConfigEndHoleTexture()
{
    return ConfigTexture{
        .path = "other/hole.png",
        .scale = {1, 1},
        .originOffset = { 0.5, 0.5 }
    };
}

ConfigTexture getDefaultConfigBackgroundTexture()
{
    return ConfigTexture{
        .path = "other/background.png",
        .scale = { 1, 1 },
        .originOffset = { 0, 0 }
    };
}

ConfigTextures getDefaultConfigTextures()
{
    return ConfigTextures{
        .path = "textures",
        .scale = { 1, 1 },
        .player = getDefaultConfigPlayerTexture(),
        .enemy = getDefaultConfigEnemyTexture(),
        .jetpack = getDefaultConfigJetpackAnimation(),
        .shield = getDefaultConfigShieldAnimation(),
        .platform = getDefaultConfigPlatformAnimation(),
        .endHole = getDefaultConfigEndHoleTexture(),
        .background = getDefaultConfigBackgroundTexture()
    };
}

ConfigFont getDefaultConfigDefaultFont()
{
    return ConfigFont{
        .path = "default",
        .letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789$:?!",
        .scale = { 1, 1 },
        .originOffset = { 0.5, 0.5 },
        .kerning = { -30, -30 }
    };
}

ConfigFonts getDefaultConfigFonts()
{
    return ConfigFonts{
        .path = "fonts",
        .scale = { 1, 1 },
        .defaultFont = getDefaultConfigDefaultFont()
    };
}

ConfigResources getDefaultConfigResources()
{
    return ConfigResources{
        .path = "../res",
        .scale = { 1, 1 },
        .textures = getDefaultConfigTextures(),
        .fonts = getDefaultConfigFonts()
    };
}
