#include "Simulation.h"

#include "Application/Application.h"
#include "Application/AppPartGetter.h"
#include "Application/Config/ConfigGeneral.h"
#include "Application/Details/Logger.h"
#include "GameLevels/Base/LevelsManager.h"
#include "Simulation/ECS/ECS.h"
#include "Simulation/GameLevels/Base/UserLevelBase.h"
#include "Simulation/Features/Timer/CTimer.h"

void Simulation::Init()
{
    Log("Init simulation");
    currentLevel = getLevelsManager().LoadLevel(getConfig().simulation.configLevels.level1);

    listenerKeyPressed.SubscribeEmitter(Application::GetInstance().emitterKeyPressed);
    listenerKeyReleased.SubscribeEmitter(Application::GetInstance().emitterKeyReleased);
    listenerMouseButtonClicked.SubscribeEmitter(Application::GetInstance().emitterMouseClicked);
    listenerMouseMoved.SubscribeEmitter(Application::GetInstance().emitterMouseMoved);

}

bool Simulation::Update(float dt)
{
    if (!currentLevel)
    {
        Log("Any game level aren't loaded", Logger::Verbosity::CRITICAL);
    }

    passedTime += dt;
    if (passedTime - lastUpdateTime < 1/getConfig().simulation.fps)
    {
        return true;
    }

    bool isUpdated = currentLevel->Update(1/getConfig().simulation.fps);
    if (!isUpdated)
    {
        Log("Level isn't updated. RESTART LEVEL", Logger::Verbosity::WARNING);
        currentLevel = getLevelsManager().LoadLevel(getConfig().simulation.configLevels.level1);
    }

    return true;
}

void Simulation::Draw(Vector2f pos) const
{
    currentLevel->Draw(pos);
}

void Simulation::OnKeyPressed(FRKey& e)
{
    currentLevel->GetInputInjector().InjectKeyEvent({e, true});
}

void Simulation::OnKeyReleased(FRKey& e)
{
    currentLevel->GetInputInjector().InjectKeyEvent({e, false});
}

void Simulation::OnMouseButtonClicked(FRMouseButtonClick& click)
{
    currentLevel->GetInputInjector().InjectMouseClick(click.position);
}

void Simulation::OnMouseMoved(Vector2i& newPos)
{
    currentLevel->GetInputInjector().InjectMousePosition(Vector2f(newPos));
}
