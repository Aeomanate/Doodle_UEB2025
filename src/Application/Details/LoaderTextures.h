#ifndef TEXTURESCACHE_H
#define TEXTURESCACHE_H

#include "Application/AssetsStorage.h"
#include "Application/AppPartGetter.h"
#include "Application/Sprite/CustomSprite.h"

#include "LoaderTextures.h"

template<class StructEntry>
struct FullFilenames;

template<class T>
concept HasPath = requires(T& entry)
{
    { entry.path } -> std::convertible_to<fs::path&>;
};
template<class T>
concept IsResource = std::is_convertible_v<T, ConfigResources>;
template<class T>
concept IsAnim = std::is_convertible_v<T, ConfigAnimation>;
template<class T>
concept IsFont = std::is_convertible_v<T, ConfigFont>;
template<class T>
concept IsTexture = std::is_convertible_v<T, ConfigTexture>;
template<class T>
concept IsSeveralTextures = IsAnim<T> || IsFont<T>;
template<class T>
concept IsAggregator = HasPath<T> and !IsSeveralTextures<T> && !IsTexture<T>;

template<IsAggregator StructEntry>
struct FullFilenames<StructEntry>
{
    static void CreateSprites(fs::path curPath, StructEntry& entry, Vector2f scale)
    {
        curPath.make_preferred();
        Log("Collecting fields from config", curPath.string());

        auto view = rfl::to_view(entry);
        view.apply([curPath, scale](auto& rflField) {
            auto name = rflField.name();

            auto& innerStructEntry = *rflField.value();

            using InnerStructT = std::remove_reference_t<decltype(innerStructEntry)>;
            if constexpr (HasPath<InnerStructT>)
            {
                FullFilenames<InnerStructT>::CreateSprites(
                    curPath / innerStructEntry.path,
                    innerStructEntry,
                    scale * innerStructEntry.scale
                );
            }
        });
    }
};

template<IsSeveralTextures StructEntry>
struct FullFilenames<StructEntry>
{
    static void CreateSprites(fs::path curPath, StructEntry& entry, Vector2f scale)
    {
        curPath.make_preferred();
        std::error_code ec;
        if (!fs::exists(curPath, ec) || !fs::is_directory(curPath, ec))
        {
            Log("Sprite directory does not exist or is not a directory",
                curPath.string(),
                Logger::Verbosity::CRITICAL);
            return;
        }

        for (auto& dirEntry: fs::directory_iterator(curPath, ec))
        {
            if (fs::is_regular_file(dirEntry.path()))
            {
                Log("Collecting path", dirEntry.path().string(), Logger::Verbosity::GABBY);
                auto it = getAssetsStorage().Store(
                    dirEntry.path().string(),
                    CustomSprite(dirEntry.path().string(), entry.originOffset, scale * entry.scale)
                );

                entry.sprites().push_back(&it->second);
            }
            else
            {
                Log("Not a regular file in a sprite-sheet dir",
                    dirEntry.path().string(),
                    Logger::Verbosity::WARNING);
            }
        }
        entry.sprites().shrink_to_fit();
    }
};

template<IsTexture StructEntry>
struct FullFilenames<StructEntry>
{
    static void CreateSprites(fs::path curPath, ConfigTexture& entry, Vector2f scale)
    {
        curPath.make_preferred();
        if (fs::is_regular_file(curPath))
        {
            Log("Collected path", curPath.string(), Logger::Verbosity::GABBY);
            auto it = getAssetsStorage().Store(
                curPath.string(),
                CustomSprite(curPath.string(), entry.originOffset, scale * entry.scale)
            );

            entry.sprite = &it->second;
        }
        else
        {
            Log("Expected regular file. It's not a regular file",
                curPath.string(),
                Logger::Verbosity::WARNING);
        }
    }
};

inline void loadTextures()
{
    Log("Load textures");
    FullFilenames<ConfigResources>::CreateSprites(
        getConfig().resources.path,
        getConfig().resources,
        getConfig().window.scalaRatio()
    );
}


#endif //TEXTURESCACHE_H
