#ifndef RESOURCESCACHE_H
#define RESOURCESCACHE_H


#include "Singleton.h"
#include "Application/AppPartGetter.h"
#include "Application/Config/ConfigGeneral.h"
#include "Details/Logger.h"

class AssetsStorage
{
    template <class T>
    using Map = std::unordered_map<std::string, T>;

public:
    template <class T>
    T& Get(std::string_view name)
    {
        Log("Requested resource", name, Logger::Verbosity::VERBOSE);
        return getMap<T>().at(name);
    }

    template <class T>
    Map<T>::iterator Store(std::string name, T&& value)
    {
        Log("Storing resource",
            std::format("Type({}), file: {}", typeid(T).name(), name),
            Logger::Verbosity::VERBOSE);

        auto [it, isSuccess] = getMap<T>().try_emplace(name, std::move(value));
        if(!isSuccess)
        {
            Log("Resource wasn't inserted to the map",
                name.data() + "\""s,
                Logger::Verbosity::WARNING);
        }
        return it;
    }

private:
    template <class T>
    Map<T>& getMap()
    {
        static Map<T> map;
        return map;
    }

};

#endif //RESOURCESCACHE_H
