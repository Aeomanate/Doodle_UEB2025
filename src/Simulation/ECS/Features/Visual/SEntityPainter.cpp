#include "SEntityPainter.h"

#include "SViewport.h"
#include "Application/AppPartGetter.h"
#include "Simulation/ECS/ECS.h"
#include "Simulation/ECS/Features/LifetimeControl/CActivityTags.h"

SEntityPainter::SEntityPainter()
: ECS::System(ECS::System::Order::RENDER)
{ }

bool SEntityPainter::Update(float)
{
    for(ECS::Entity* entity: ECS::Concat<CAnimation, CSprite>() | CTagActive::Filter() | CZOrder::Sort())
    {
        ScenePosition& position = entity->Get<CPosition>();

        DrawNode data {
            .sprite=extractCustomSprite(entity),
            .position=SViewport::ToLocal(position.cur)
        };
        emitterDrawRequest.Emit(data);
    }
    return true;
}
