#ifndef SPRITE_H
#define SPRITE_H

#include "3rd-party/Framework.h"
#include "Application/Details/Drawable.h"
#include "Math/Rect.h"
#include "Math/Vector2.h"

class CustomSprite: public Drawable
{
public:
    // Component of originOffsetRatio is a value from 0 to 1 and describes
    // where will be the center of drawing (default is a top-left corner)
    // If you set (1; 1), it will be the bottom-right corner.
    CustomSprite(std::string_view name, Vector2f originOffsetRatio = {0.5, 0.5}, Vector2f scale = { 1, 1 });
    CustomSprite(CustomSprite &&) noexcept = default;

    void Draw(Vector2f pos) const override;

    Vector2i GetSize() const;

    Vector2f GetOriginOffsetRatio() const;

    Vector2f GetShiftValue() const;

    RectF GetScreenRect(Vector2f pos) const;

    void SetSize(Vector2i size);

private:
    mutable FRSprite rawSprite;
    Vector2f originOffsetRatio;
};



#endif //SPRITE_H
