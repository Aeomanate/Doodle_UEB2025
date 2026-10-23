#ifndef CSCENEELEMENT_H
#define CSCENEELEMENT_H


#include "Application/Sprite/FrameAnimation.h"
#include "Simulation/ECS/Component.h"
#include "Simulation/ECS/Features/Movable/CPosition.h"

enum class ZOrder
{
    UNDEFINED,
    BACKGROUND,
    PLATFORMS,
    ENEMIES,
    PROJECTILES,
    PLAYER,
    ACCESSORY,
    GUI,
};

struct CZOrder: ECS::Component<CZOrder, ZOrder>
{ };

template<
    class UserElementType,
    class GraphicsType = std::conditional_t
    <
     std::is_same_v<UserElementType, FrameAnimation>,
     FrameAnimation,
     const CustomSprite*
    >
>
    requires
    std::is_convertible_v<UserElementType, FrameAnimation>
    || std::is_convertible_v<UserElementType, CustomSprite>
struct CSceneElement : public ECS::Component<CSceneElement<UserElementType>, GraphicsType>
{

};

using CAnimation = CSceneElement<FrameAnimation>;
using CSprite = CSceneElement<CustomSprite>;

template <class EntityT>
const CustomSprite* extractCustomSprite(EntityT* entity)
{
    const CustomSprite** spriteNode = entity->template TryGet<CSprite>();
    const CustomSprite* customSprite = spriteNode ? *spriteNode : entity->template Get<CAnimation>().getCurSprite();

    return customSprite;
}

#endif //CSCENEELEMENT_H
