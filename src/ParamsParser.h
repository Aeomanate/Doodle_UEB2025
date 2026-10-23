#ifndef PARAMSPARSER_H
#define PARAMSPARSER_H

#include "Application/Config/ConfigGeneral.h"

struct ExpectedParam
{
    ExpectedParam(const char* paramS, const char* argsS);

    std::regex param;
    std::regex args;
};

ConfigWindow parseResolution(int argc, char* argv[]);


#endif //PARAMSPARSER_H
