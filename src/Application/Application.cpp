#include "Application.h"

#include "Config/MainConfig.h"
#include "Simulation/Simulation.h"
#include "Details/LoaderTextures.h"
#include "Math/Random.h"

void Application::InitListeners()
{
    Log("Init listeners");
    listenerKeyEvent.SubscribeEmitter(emitterKeyPressed);
    listenerKeyEvent.SubscribeEmitter(emitterKeyReleased);
    // listenerLastMenuClosed.SubscribeEmitter(getMenuLayer().emitterLastMenuClosed);
}

void Application::InitGameRelated()
{
    loadTextures();
#ifndef NDEBUG
    Random::Init(false);
#else
    Random::Init(true);
#endif
    getSimulation().Init();
}

int Application::Run(std::optional<ConfigWindow> configWindow)
{
    Logger::CurrentLogLevel = Logger::Verbosity::VERBOSE;

    auto defaultPath = getDefaultConfigPath();
    getMainConfig().Init(defaultPath.configFolder, defaultPath.configName);
    getMainConfig().LoadOrCreate();
    if (configWindow.has_value())
    {
        getConfig().window = *configWindow;
    }

    Log("\n\n"s + "Starting application...");
    InitListeners();

    return LowLevelApplication::Run(configWindow);
}

bool Application::Init()
{
    Log("Init application");
    InitGameRelated();
    WindowsRelated::AdjustWindowPosition(getConfig().window.screenSize);
    return LowLevelApplication::Init();
}

void Application::Update(float dt)
{
    isWorking = getSimulation().Update(dt);
}

void Application::Draw(Vector2f pos) const
{
    getSimulation().Draw(pos);
}

void Application::Close()
{
    Log("Closing application");

    getMainConfig().Save();

    LowLevelApplication::Close();
}

unsigned Application::TimeSinceStartMs() const
{
    return getTickCount();
}

void Application::OnLastMenuClosed()
{
    isWorking = false;
}

void Application::OnKeyEvent(FRKey& key)
{

}


