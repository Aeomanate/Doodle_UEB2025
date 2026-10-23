// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "ParamsParser.h"
#include "Application/Details/Logger.h"

ExpectedParam::ExpectedParam(const char* paramS, const char* argsS)
: param(paramS)
, args(argsS)
{ }

std::optional<ConfigWindow> parseResolution(int argc, char* argv[])
{
    std::vector<ExpectedParam> expectedParams = {
        { R"(-window)", R"((\d+)x(\d+))" }
    };

    std::optional<ConfigWindow> config;

    for (int i = 1; i < argc; i++)
    {
        for (auto const& param: expectedParams)
        {
            std::string paramStr(argv[i]);
            if (!std::regex_match(paramStr, param.param))
            {
                continue;
            }

            if (i + 1 >= argc)
            {
                return std::nullopt;
            }
            std::string valueStr(argv[i + 1]);
            std::smatch argsMatch;

            if (!std::regex_match(valueStr, argsMatch, param.args))
            {
                continue;
            }

            // Convert captured groups to integers
            auto m1 = argsMatch[1].str();
            auto m2 = argsMatch[2].str();

            ConfigWindow newConfig = getDefaultConfigWindow();
            auto [ec1, ec2] = std::tuple{
                std::from_chars(m1.c_str(), m1.c_str() + m1.length(), newConfig.screenSize.x).ec,
                std::from_chars(m2.c_str(), m2.c_str() + m2.length(), newConfig.screenSize.y).ec
            };
            if (ec1 != std::errc{ } or ec2 != std::errc{ })
            {
                Log("Failed to parse screen size value", Logger::Verbosity::WARNING);
                return std::nullopt;
            }

            config = newConfig;
            ++i; // Skip the next argument since we've processed it
        }
    }

    return config;
}
