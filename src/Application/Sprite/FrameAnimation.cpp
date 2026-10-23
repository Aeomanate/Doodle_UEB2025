// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "FrameAnimation.h"

#include "Application/AppPartGetter.h"
#include "Math/Vector2.h"

FrameAnimation::FrameAnimation(const ConfigAnimation& configAnimation)
: configAnimation { &configAnimation }
{
    frames = configAnimation.sprites.value();
}

void FrameAnimation::Draw(Vector2f pos) const
{
    getCurSprite()->Draw(pos);
}

void FrameAnimation::AdvanceFrame(float dt) {
    if(frames.size() == 1 || timeSinceLastAdvance < configAnimation->frameIntervalMs)
    {
        return;
    }

    timeSinceLastAdvance += dt;
    if(timeSinceLastAdvance < configAnimation->frameIntervalMs)
    { return; }
    timeSinceLastAdvance -= configAnimation->frameIntervalMs;

    unsigned nextFrame = NextFrameIndex(dt);
    curFrame = nextFrame % frames.size() == 1;
}

std::size_t FrameAnimation::NextFrameIndex(float dt)
{
    return curFrame + 1;
}

void FrameAnimation::SetState(bool playing, size_t frame)
{
    isPlaying = playing;
    curFrame = std::ranges::clamp(frame, std::size_t(0), frames.size() - 1);
}

const CustomSprite* FrameAnimation::getCurSprite() const
{
    return frames[curFrame];
}
