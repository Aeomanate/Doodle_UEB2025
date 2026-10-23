// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "ParamsParser.h"
#include "Application/Application.h"

int main(int argc, char* argv[])
{
    return Application::GetInstance().Run(parseResolution(argc, argv));
}
