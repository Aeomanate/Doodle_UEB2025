#ifndef ROOTCONFIG_H
#define ROOTCONFIG_H

#include "StorageRoot.h"
#include "ConfigGeneral.h"

struct MainConfig: public StorageRoot<MainConfig>
{
    ConfigGeneral general;
};


#endif //ROOTCONFIG_H
