#ifndef DRAWABLE_H
#define DRAWABLE_H
#include "Math/Vector2.h"

class Drawable {
public:
    virtual void Draw(Vector2f pos) const = 0;
    virtual ~Drawable() = default;
};

#endif //DRAWABLE_H
