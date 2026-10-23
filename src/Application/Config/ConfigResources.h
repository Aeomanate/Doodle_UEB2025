#ifndef CONFIGRESOURCES_H
#define CONFIGRESOURCES_H


#include "Application/Sprite/CustomSprite.h"
#include "Math/Vector2.h"
using namespace std::string_literals;
namespace fs = std::filesystem;

// ==========================================================================

struct ConfigTexture
{
    fs::path path;
    Vector2f scale;
    Vector2f originOffset;

    rfl::Skip<const CustomSprite*> sprite;
};

struct ConfigCharacterTexture
{
    fs::path path;
    Vector2f scale;
    Vector2f originOffset;
    ConfigTexture left;
    ConfigTexture right;
    ConfigTexture idle;
};

struct ConfigAnimation
{
    fs::path path;
    Vector2f scale;
    Vector2f originOffset;
    float durationS;
    float frameIntervalMs;

    // A texture index starts from 1
    // because of how photoshop is importing spreadsheets separately
    std::vector<unsigned> startFrames;
    std::vector<unsigned> repeatFrames;
    std::vector<unsigned> finishFrames;
    std::vector<unsigned> idleFrames;

    rfl::Skip<std::vector<const CustomSprite*>> sprites;
};

// ==========================================================================

struct ConfigTextures
{
    fs::path path;
    Vector2f scale;

    ConfigCharacterTexture player;
    ConfigCharacterTexture enemy;
    ConfigAnimation jetpack;
    ConfigAnimation shield;
    ConfigAnimation platform;
    ConfigTexture endHole;
    ConfigTexture background;
};

// ==========================================================================

struct ConfigFont
{
    fs::path path;
    std::string letters;
    Vector2f scale;
    Vector2f originOffset;
    Vector2i kerning; // An offset of top-right corner while drawing

    rfl::Skip<std::vector<const CustomSprite*>> sprites;
};

struct ConfigFonts
{
    fs::path path;
    Vector2f scale;

    ConfigFont defaultFont;
};

// ==========================================================================

struct ConfigResources
{
    fs::path path;
    Vector2f scale;
    ConfigTextures textures;
    ConfigFonts fonts;
};

// ==========================================================================
// Factory functions for default initialization
// ==========================================================================

ConfigTexture getDefaultConfigTexture(const fs::path& path = "filename", 
    const Vector2f& scale = {1, 1}, const Vector2f& originOffset = {0, 0});
ConfigCharacterTexture getDefaultConfigPlayerTexture();
ConfigCharacterTexture getDefaultConfigEnemyTexture();
ConfigAnimation getDefaultConfigJetpackAnimation();
ConfigAnimation getDefaultConfigShieldAnimation();
ConfigAnimation getDefaultConfigPlatformAnimation();
ConfigTexture getDefaultConfigEndHoleTexture();
ConfigTexture getDefaultConfigBackgroundTexture();
ConfigTextures getDefaultConfigTextures();
ConfigFont getDefaultConfigDefaultFont();
ConfigFonts getDefaultConfigFonts();
ConfigResources getDefaultConfigResources();

#endif //CONFIGRESOURCES_H
