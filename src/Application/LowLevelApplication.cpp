#include "LowLevelApplication.h"

#include "Application.h"
#include "AppPartGetter.h"
#include "Application/AppPartGetter.h"
#include "Config/ConfigGeneral.h"
#include "Config/MainConfig.h"

LowLevelApplication::LowLevelApplication()
: AeoGameFramework(
    FRSize{ (int)ConfigWindow::defaultScreenSize.x, (int)ConfigWindow::defaultScreenSize.y },
    FRSize{ (int)ConfigWindow::defaultScreenSize.x, (int)ConfigWindow::defaultScreenSize.y },
    "DoodleJump for UE Bootcamp 2025 by Aeomanate",
    false
)
{
}

int LowLevelApplication::Run(std::optional<ConfigWindow>)
{
    Log("Run base framework");
    return run(this);
}

// =================================================================================

void LowLevelApplication::OnKeyPressed(FRKey key)
{
    std::string kjson = rfl::json::write(key);
    Log("Pressed",
        std::format("{}", kjson.c_str()),
        Logger::Verbosity::VERBOSE);
    emitterKeyPressed.Emit(key);
}
void LowLevelApplication::OnKeyReleased(FRKey key)
{
    std::string kjson = rfl::json::write(key);
    Log("Released",
        std::format("{}", kjson.c_str()),
        Logger::Verbosity::VERBOSE);
    emitterKeyReleased.Emit(key);
}
void LowLevelApplication::OnMouseButtonPressed(FRMouseButton button)
{
    std::string bjson = rfl::json::write(button);
    Log("Clicked",
        std::format("[{}] {} false", lastMousePos, bjson.c_str()),
        Logger::Verbosity::VERBOSE);

    FRMouseButtonClick data {
        .position=lastMousePos,
        .button=button,
        .isPressed=true
    };
    emitterMouseClicked.Emit(data);
}
void LowLevelApplication::OnMouseButtonReleased(FRMouseButton button)
{
    std::string bjson = rfl::json::write(button);
    Log("Clicked",
        std::format("[{}] {} true", lastMousePos, bjson.c_str()),
        Logger::Verbosity::VERBOSE);

    FRMouseButtonClick data {
        .position=lastMousePos,
        .button=button,
        .isPressed=false
    };
    emitterMouseClicked.Emit(data);
}
void LowLevelApplication::OnMouseMove(int x, int y, int xrelative, int yrelative)
{
    (void)xrelative;
    (void)yrelative;
    lastMousePos = Vector2i{ x, y };
    emitterMouseMoved.Emit(lastMousePos);
}

// =================================================================================

bool LowLevelApplication::Init()
{
    Log("Init base framework");
    return true;
}

bool LowLevelApplication::Tick()
{
    unsigned msPassedUpdated = (unsigned)getTickCount();

    Update(float(msPassedUpdated - msPassed) / 1000.f);

    msPassed = msPassedUpdated;

    Draw({0, 0});

    return isWorking;
}

void LowLevelApplication::Close()
{

}
