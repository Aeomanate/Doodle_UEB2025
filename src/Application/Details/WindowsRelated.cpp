#include "Application/Details/WindowsRelated.h"

void WindowsRelated::ShowConsole()
{
    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

void WindowsRelated::HideConsole()
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

bool WindowsRelated::CreateDirWhenAbsent(const fs::path& directory)
{
    if(fs::exists(directory))
    {
        return true;
    } else
    {
        Log("Folder isn't exist", directory.string());
    }

    bool isCreated = fs::create_directories(directory);

    if(!isCreated)
    {
        Log("Folder cannot be created", directory.string(), Logger::Verbosity::WARNING);
    }

    return isCreated;
}
