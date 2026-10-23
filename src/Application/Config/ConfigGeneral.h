#ifndef GENERALCONFIG_H
#define GENERALCONFIG_H


#include "ConfigSimulation.h"
#include "ConfigResources.h"

struct ConfigPath
{
    fs::path configFolder;
    std::string configName;

    fs::path logFolder;
    std::string logName;
};

struct ConfigWindow
{
    std::string appName;
    Vector2u screenSize;
    bool fullscreen;

    static const Vector2u defaultScreenSize;
    Vector2f scalaRatio()
    {
        return Vector2f(screenSize) / defaultScreenSize;
    }
};

struct ConfigGeneral
{
    ConfigPath configPath;
    ConfigResources resources;
    ConfigWindow window;
    ConfigSimulation simulation;
};

// ==========================================================================
// Factory functions for default initialization
// ==========================================================================

ConfigPath getDefaultConfigPath();
ConfigWindow getDefaultConfigWindow();
ConfigGeneral getDefaultConfigGeneral();

#endif //GENERALCONFIG_H
