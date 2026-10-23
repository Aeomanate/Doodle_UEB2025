#ifndef GETTERFONTPROVIDER_H
#define GETTERFONTPROVIDER_H

struct MainConfig;
class LevelsManager;
struct ConfigGeneral;
class LevelsFabric;
class AssetsStorage;
class Simulation;

MainConfig& getMainConfig();

ConfigGeneral& getConfig();

LevelsManager& getLevelsManager();

LevelsFabric& getFabricLevels();

AssetsStorage& getAssetsStorage();

Simulation& getSimulation();


#endif //GETTERFONTPROVIDER_H
