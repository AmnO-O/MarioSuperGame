#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "raylib.h"
#include <string>
#include <unordered_map>

class ResourceManager {
public:
    static ResourceManager& getInstance();

    Texture2D& loadTexture(const std::string& name, const std::string& filename);
    Texture2D& getTexture(const std::string& name);
    void unloadAll();

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;

private:
    ResourceManager() = default;
    ~ResourceManager() = default;

    std::unordered_map<std::string, Texture2D> textures;
};

#endif
