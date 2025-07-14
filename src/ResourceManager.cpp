#include "ResourceManager.h"

// Singleton instance
ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

Texture2D& ResourceManager::loadTexture(const std::string& name, const std::string& filename) {
    if (textures.find(name) == textures.end()) {
        textures[name] = LoadTexture(filename.c_str());
    }
    return textures[name];
}

Texture2D& ResourceManager::getTexture(const std::string& name) {
    return textures.at(name);
}

void ResourceManager::unloadAll() {
    for (auto& [name, tex] : textures) {
        UnloadTexture(tex);
    }
    textures.clear();
}
