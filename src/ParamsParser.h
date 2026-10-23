#ifndef PARAMSPARSER_H
#define PARAMSPARSER_H

#include <optional>
#include <regex>
#include "Application/Config/ConfigGeneral.h"

struct ExpectedParam
{
    ExpectedParam(const char* paramS, const char* argsS);

    std::regex param;
    std::regex args;
};

std::optional<ConfigWindow> parseResolution(int argc, char* argv[]);


#endif //PARAMSPARSER_H
