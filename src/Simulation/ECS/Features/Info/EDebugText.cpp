#include "EDebugText.h"

#include "Application/AppPartGetter.h"
#include "Application/Config/ConfigGeneral.h"
#include "Simulation/ECS/ECS.h"

EDebugText::EDebugText()
: ECS::Entity("EDebugText")
{
    Claim<CText>().SetFont(getConfig().resources.fonts.defaultFont);
    Claim<CPosition>();
}
