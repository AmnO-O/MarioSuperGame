#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "raylib.h"
#include <string>
#include <unordered_map>

class ResourceManager {
public:
    static Texture2D& loadTexture(const std::string& name, const std::string& filename);
    static Texture2D& getTexture(const std::string& name);
    static void unloadAll();

private:
    static std::unordered_map<std::string, Texture2D> textures;
};

#endif
