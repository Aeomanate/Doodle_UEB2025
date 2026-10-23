#ifndef TEXT_H
#define TEXT_H

#include "Font.h"

class Text {
public:
    void SetFont(const ConfigFont& configFont);
    void SetString(const std::string& string);

private:
    Font font;
};



#endif //TEXT_H
