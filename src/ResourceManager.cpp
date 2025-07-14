#include "ResourceManager.h"

std::unordered_map<std::string, Texture2D> ResourceManager::textures;
std::unordered_map<std::string, Font> ResourceManager::fonts;
std::unordered_map<std::string, Sound> ResourceManager::sounds;

Texture2D& ResourceManager::loadTexture(const std::string& name, const std::string& filename) {
    if (textures.find(name) == textures.end()) {
        textures[name] = LoadTexture(filename.c_str());
    }
    return textures[name];
}

Texture2D& ResourceManager::getTexture(const std::string& name) {
    return textures.at(name);
}

Font& ResourceManager::getFont(const std::string& name) {
    return fonts.at(name);
}

Sound& ResourceManager::getSound(const std::string& name) {
    return sounds.at(name);
}

void ResourceManager::loadAllFonts(const std::string& path) {
	for (auto& file : std::filesystem::directory_iterator(path)) {
		if (file.is_regular_file()) {
			auto ext = file.path().extension().string();
			if (ext == ".ttf") {
                std::string name = file.path().stem().string();
				textures[name] = LoadTexture(file.path().string().c_str());
			}
		}
	}
}

void ResourceManager::loadAllSounds(const std::string& path) {
	for (auto& file : std::filesystem::directory_iterator(path)) {
		if (file.is_regular_file()) {
			auto ext = file.path().extension().string();
			if (ext == ".wav" || ext == ".mp3") {
                std::string name = file.path().stem().string();
				textures[name] = LoadTexture(file.path().string().c_str());
			}
		}
	}
}

void ResourceManager::loadAllTextures(const std::string& path) {
	for (auto& file : std::filesystem::directory_iterator(path)) {
		if (file.is_regular_file()) {
			auto ext = file.path().extension().string();
			if (ext == ".png" || ext == ".jpg") {
                std::string name = file.path().stem().string();
				textures[name] = LoadTexture(file.path().string().c_str());
			}
		}
	}
}

void ResourceManager::unloadAll() {
    for (auto& [name, tex] : textures) {
        UnloadTexture(tex);
    }

    for(auto& [name, font] : fonts){
        UnloadFont(font); 
    }

    for(auto& [name, sound] : sounds){
        UnloadSound(sound); 
    }

    textures.clear();
    fonts.clear(); 
    sounds.clear(); 
}
