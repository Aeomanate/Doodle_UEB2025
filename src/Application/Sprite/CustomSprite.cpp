#include "CustomSprite.h"

#include "Simulation/ECS/Features/Visual/SViewport.h"


CustomSprite::CustomSprite(std::string_view name, Vector2f originOffsetRatio, Vector2f scale)
: rawSprite(std::string(name).c_str())
, originOffsetRatio { originOffsetRatio.x, originOffsetRatio.y }
{
    SetSize(scale * GetSize());
}

void CustomSprite::Draw(Vector2f pos) const
{
    Vector2i resultPos = pos - GetShiftValue();
    rawSprite.Draw(resultPos.x, resultPos.y);
}

Vector2i CustomSprite::GetSize() const
{
    FRSize size = rawSprite.GetSizeWH();
    return { size.w, size.h };
}

Vector2f CustomSprite::GetOriginOffsetRatio() const
{
    return originOffsetRatio;
}

Vector2f CustomSprite::GetShiftValue() const
{
    return GetSize() * originOffsetRatio;
}

RectF CustomSprite::GetScreenRect(Vector2f pos) const
{
    return RectF{ SViewport::ToScreen(pos) - GetShiftValue(), GetSize() };
}

void CustomSprite::SetSize(Vector2i size)
{
    rawSprite.SetSize(size.x, size.y);
}

