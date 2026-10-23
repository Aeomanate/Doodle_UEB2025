#ifndef STORAGEROOT_H
#define STORAGEROOT_H

#include "Application/Details/WindowsRelated.h"
namespace fs = std::filesystem;

struct ConfigGeneral;
ConfigGeneral getDefaultConfigGeneral();

// When true, always overwrite config.json with factory defaults on startup.
// Set to false to persist config changes across runs.
constexpr bool kForceRegenerateConfig = true;

template<class Derived>
class StorageRoot
{
public:
    StorageRoot() = default;
    virtual ~StorageRoot() = default;

    void Init(const fs::path& storageFolder, const std::string_view storageFilename)
    {
        folder = storageFolder;
        filename = storageFilename;
    }

    void LoadOrCreate()
    {
        if (kForceRegenerateConfig)
        {
            auto& derivedConfig = static_cast<Derived&>(*this).general;
            derivedConfig = getDefaultConfigGeneral();
            Save();
            Log("Config regenerated from defaults (kForceRegenerateConfig = true)");
        }
        else
        {
            if(!Load())
            {
                auto& derivedConfig = static_cast<Derived&>(*this).general;
                derivedConfig = getDefaultConfigGeneral();
                Save();
            }
        }
    }

    bool Load()
    {
        auto& derivedConfig = static_cast<Derived&>(*this).general;
        using ConfigTypeT = std::remove_reference_t<decltype(derivedConfig)>;

        std::ifstream in = WindowsRelated::StreamOpen<std::ifstream>(folder, filename);

        rfl::Result<ConfigTypeT> result = rfl::json::read<ConfigTypeT>(in);
        if(!result.has_value())
        {
            Log("Config parse failed",
                (folder / filename).string() + "\n" + result.error().what(),
                Logger::Verbosity::WARNING);
            return result.has_value();
        }

        Log("Config loaded");
        derivedConfig = std::move(*result);

        return result.has_value();
    }

    bool Save()
    {
        std::ofstream out = WindowsRelated::StreamOpen<std::ofstream>(folder, filename);
        auto const& derivedConfig = static_cast<Derived&>(*this).general;
        rfl::json::write(derivedConfig, out);
        if(!out)
        {
            Log("Writing config failed",
                (folder / filename).string(),
                Logger::Verbosity::WARNING);
        }

        return bool(out);
    }

protected:
    fs::path folder{};
    std::string filename{};
};


#endif //STORAGEROOT_H
