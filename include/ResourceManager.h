#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "raylib.h"
#include <string>
#include <unordered_map>
#include <filesystem>

class ResourceManager {
public:
    static Texture2D& loadTexture(const std::string& name, const std::string& filename);

    static Texture2D& getTexture(const std::string& name);
    static Font& getFont(const std::string& name);
    static Sound& getSound(const std::string& name);

	static void loadAllTextures(const std::string& folderPath);
	static void loadAllFonts(const std::string& folderPath);
	static void loadAllSounds(const std::string& folderPath);

    static void unloadAll();

private:
    static std::unordered_map<std::string, Texture2D> textures;
    static std::unordered_map<std::string, Font> fonts;
    static std::unordered_map<std::string, Sound> sounds; 
};

#endif
