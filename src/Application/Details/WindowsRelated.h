#ifndef SYSTEMRELATED_H
#define SYSTEMRELATED_H

#include "Logger.h"
#include "Math/Vector2.h"

namespace fs = std::filesystem;

class WindowsRelated
{
public:
    static void ShowConsole();
    static void HideConsole();
    static bool CreateDirWhenAbsent(const fs::path& directory);

    template<class Stream>
    static Stream StreamOpen(fs::path& folder, const std::string& name)
    {
        if (!WindowsRelated::CreateDirWhenAbsent(folder))
        {
            return { };
        }

        fs::path pathToOpen = folder / name;
        if (!fs::exists(pathToOpen))
        {
            Log("File is absent: ", pathToOpen.string());
            Log("Creating file: ", pathToOpen.string());
        }

        Stream stream(pathToOpen);

        if (!stream)
        {
            Log("Failed: ", pathToOpen.string(), Logger::Verbosity::WARNING);
        }

        return stream;
    }

    static void AdjustWindowPosition(Vector2u windowSize)
    {
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);

        int windowX = (screenWidth - windowSize.x) / 2;
        int windowY = (screenHeight - windowSize.y) / 2;

        if (windowX < 0)
        {
            windowX = 0;
            Log("Warning: Window width exceeds screen width");
        }
        if (windowY < 0)
        {
            windowY = 0;
            Log("Warning: Window height exceeds screen height");
        }

        HWND hwnd = GetActiveWindow();
        if (hwnd)
        {
            SetWindowPos(hwnd, nullptr, windowX, windowY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
        }
        else
        {
            Log("Error: Could not get window handle");
        }
    }
};


#endif //SYSTEMRELATED_H
