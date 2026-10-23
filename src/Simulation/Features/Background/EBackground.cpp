#include "EBackground.h"

#include "CTagBackground.h"
#include "Application/AppPartGetter.h"
#include "Application/Config/ConfigGeneral.h"
#include "Simulation/ECS/ECS.h"
#include "Simulation/ECS/Features/LifetimeControl/CActivityTags.h"
#include "Simulation/ECS/Features/Movable/CCanCollide.h"
#include "Simulation/ECS/Features/Visual/SViewport.h"

EBackground::EBackground()
: ECS::Entity("Background")
{
    Claim<CTagBackground>();

    Claim<CSprite>() = getConfig().resources.textures.background.sprite();
    Claim<CZOrder>() = ZOrder::BACKGROUND;
    Claim<CPosition>() = {0, SViewport::Get().size.y };
    Claim<CCanCollide>() = false;
    Claim<CTagActive>();
}
