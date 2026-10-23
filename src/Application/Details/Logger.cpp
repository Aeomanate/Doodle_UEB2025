// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Logger.h"

#include "WindowsRelated.h"
#include "Application/Application.h"
#include "Application/AppPartGetter.h"
#include "Application/Config/ConfigGeneral.h"

using namespace std::string_literals;

void Logger::Log(std::string_view message, std::string_view details, Logger::Verbosity logLevel)
{
    if (!IsLogLevelAppropriate(logLevel))
    {
        return;
    }

    // For prevent recursive call
    if (!currentLogMessage.empty())
    {
        currentLogMessage += "\n-> ";
        currentLogMessage += formatLog(message, details, logLevel);
        return;
    }
    currentLogMessage = formatLog(message, details, logLevel);
    DoLog();
    currentLogMessage.clear();
}

bool Logger::IsLogLevelAppropriate(Logger::Verbosity logLevel)
{
    return logLevel >= CurrentLogLevel;
}

void Logger::DoLog()
{
    fs::path logFolder = getConfig().configPath.logFolder;
    std::string filename = getConfig().configPath.logName;
    fs::path logPath = logFolder / filename;

    if (!fs::exists(logFolder))
    {
        (currentLogMessage += "\n-> ")
            += formatLog("Creating folder", logFolder.string());
    }

    if (!WindowsRelated::CreateDirWhenAbsent(logFolder))
    {
        if (!IsLogLevelAppropriate(Logger::Verbosity::WARNING))
        {
            return;
        }
        (currentLogMessage += "\n-> ")
            += formatLog("Failed to create a folder", logFolder.string(), Logger::Verbosity::WARNING);
        showInConsole(currentLogMessage);
        return;
    }

    std::ofstream logStream;
    logStream.open(logPath, std::ios_base::app);

    if (!logStream.is_open())
    {
        if (!IsLogLevelAppropriate(Verbosity::WARNING))
        {
            return;
        }
        (currentLogMessage += "\n-> ")
            += formatLog("Cannot open log path", logPath.string(), Verbosity::WARNING);
        showInConsole(currentLogMessage);
        return;
    }

    logStream << currentLogMessage << std::endl;

#ifndef NDEBUG
    std::cout << currentLogMessage << std::endl;
#endif
}

void Logger::showInConsole(std::string& str)
{
    WindowsRelated::ShowConsole();
    std::cerr << str << '\n';
}

const std::string& Logger::getLogPrefix(Logger::Verbosity logLevel)
{
    static std::array<std::string, size_t(Logger::Verbosity::COUNT)> logPrefix{
        "G"s,
        "V"s,
        "N"s,
        "W"s,
        "E"s,
    };

    return logPrefix[static_cast<int>(logLevel)];
}

std::string Logger::formatLog(std::string_view str, std::string_view details, Logger::Verbosity logLevel)
{
    // TODO: make auto-new-line in details as variadic function
    auto elapsedMs = Application::GetInstance().TimeSinceStartMs();

    auto elapsedS = elapsedMs / 1000;
    elapsedMs %= 1000;

    auto elapsedMin = elapsedS / 60;
    elapsedS %= 60;

    return std::format(
        "[{}] "
        "[{:2}m {:2}s {:3}ms] "
        "{}",
        getLogPrefix(logLevel),
        elapsedMin, elapsedS, elapsedMs,
        details.empty() ? str : std::format("{}: {}", str, details)
    );
}
