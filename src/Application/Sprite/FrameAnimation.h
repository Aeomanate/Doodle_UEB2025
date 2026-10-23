#ifndef FUSEGAME_MEMORYTEXTURESTORAGE_HPP
#define FUSEGAME_MEMORYTEXTURESTORAGE_HPP


#include "Math/Vector2.h"
#include "Application/Config/ConfigResources.h"
#include "Application/Details/Drawable.h"

class CustomSprite;

// TODO: Split animation and single sprite
class FrameAnimation: public Drawable
{
public:
    FrameAnimation() = default;
    FrameAnimation(const ConfigAnimation& configAnimation);
    FrameAnimation(FrameAnimation&&) noexcept = default;

    void Draw(Vector2f pos) const override;

    void AdvanceFrame(float dt);

    // For complex animation with several states
    virtual std::size_t NextFrameIndex(float dt);

    void SetState(bool playing, size_t frame = std::numeric_limits<size_t>::max());

    const CustomSprite* getCurSprite() const;

    ~FrameAnimation() override = default;

private:
    const ConfigAnimation* configAnimation;

    std::vector<const CustomSprite*> frames;
    std::size_t curFrame = 0;

    float timeSinceLastAdvance = 0;
    bool isPlaying = false;
};

#endif // FUSEGAME_MEMORYTEXTURESTORAGE_HPP
