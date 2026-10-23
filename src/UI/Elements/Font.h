#ifndef FONT_H
#define FONT_H

#include "Application/Config/ConfigResources.h"
#include "Application/Sprite/CustomSprite.h"
namespace fs = std::filesystem;

class Font {
public:
    void Set(const ConfigFont& otherConfigFont);

private:
    const ConfigFont* configFont = nullptr;
};



#endif //FONT_H
