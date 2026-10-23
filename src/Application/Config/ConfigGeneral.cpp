#include "ConfigGeneral.h"

const Vector2u ConfigWindow::defaultScreenSize = { 640, 720 };

ConfigPath getDefaultConfigPath()
{
    return ConfigPath{
        .configFolder = "../res/",
        .configName = "config.json",
        .logFolder = "./logs",
        .logName = "logs.txt"
    };
}

ConfigWindow getDefaultConfigWindow()
{
    return ConfigWindow{
        .appName = "DoodleJump for UE Bootcamp 2025 by Aeomanate",
        .screenSize = {640, 720},
        .fullscreen = false
    };
}

ConfigGeneral getDefaultConfigGeneral()
{
    return ConfigGeneral{
        .configPath = getDefaultConfigPath(),
        .resources = getDefaultConfigResources(),
        .window = getDefaultConfigWindow(),
        .simulation = getDefaultConfigSimulation()
    };
}
