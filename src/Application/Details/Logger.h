#ifndef LOGGER_H
#define LOGGER_H


class Logger
{
public:
    enum class Verbosity
    {
        GABBY      = 0,
        VERBOSE    = 1,
        NOTIFY     = 2,
        WARNING    = 3,
        CRITICAL   = 4,
        COUNT
    };
    static inline Logger::Verbosity CurrentLogLevel = Logger::Verbosity::NOTIFY;

public:
    static void Log(std::string_view message, std::string_view details, Logger::Verbosity logLevel = Verbosity::NOTIFY);

    static bool IsLogLevelAppropriate(Logger::Verbosity logLevel);

private:
    static void DoLog();

    static void showInConsole(std::string& str);

    static const std::string& getLogPrefix(Logger::Verbosity logLevel);

    static std::string formatLog(std::string_view str, std::string_view details, Logger::Verbosity logLevel = Verbosity::NOTIFY);

private:
    static inline std::string currentLogMessage;
};

inline void Log(std::string_view message, std::string_view details, Logger::Verbosity logLevel)
{
    Logger::Log(message, details, logLevel);
}

inline void Log(std::string_view message, std::string_view details)
{
    Logger::Log(message, details, Logger::Verbosity::NOTIFY);
}

template <std::convertible_to<std::string> T>
inline void Log(std::string_view message, T details)
{
    Logger::Log(message, std::string(details), Logger::Verbosity::NOTIFY);
}

template <class Number> requires std::is_arithmetic_v<Number>
inline void Log(std::string_view message, Number details)
{
    Logger::Log(message, std::format("{}", details), Logger::Verbosity::NOTIFY);
}

template <class Number> requires std::is_arithmetic_v<Number>
inline void Log(std::string_view message, Number details,Logger::Verbosity logLevel)
{
    Logger::Log(message, std::format("{}", details), logLevel);
}

inline void Log(std::string_view message)
{
    Logger::Log(message, "", Logger::Verbosity::NOTIFY);
}

inline void Log(std::string_view message, Logger::Verbosity logLevel)
{
    Logger::Log(message, "", logLevel);
}


#endif //LOGGER_H
