#pragma once
#include "Character/Global.h"

std::unordered_map<std::string, Texture2D> Images::textures{};

void Images::loadAllTextures(const std::string& path) {
	for (auto& file : std::filesystem::directory_iterator(path)) {
		if (file.is_regular_file()) {
			auto ext = file.path().extension().string();
			if (ext == ".png" || ext == ".jpg") {
				std::string name = file.path().filename().string();
				textures[name] = LoadTexture(file.path().string().c_str());
			}
		}
	}
}

void Images::unloadAllTextures() {
	for (auto [key, textures] : textures) UnloadTexture(textures); 
	textures.clear(); 
}