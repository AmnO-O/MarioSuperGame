#include "Resources/SoundManager.h"

std::unordered_map<std::string, Sound> SoundManager::effects;

SoundManager& SoundManager::getInstance()
{
    static SoundManager instance;
    return instance;
}

void SoundManager::loadAllSounds(const std::string& path) {
	for (auto& file : std::filesystem::directory_iterator(path)) {
		if (file.is_regular_file()) {
			auto ext = file.path().extension().string();
			if (ext == ".wav") 
            {
				std::string name = file.path().filename().string();
				effects[name] = LoadSound(file.path().string().c_str());
			}
		}
	}
}

void SoundManager::unloadAllSounds() 
{
	for (auto [key, sounds] : effects) UnloadSound(sounds); 
	effects.clear(); 
}

float SoundManager::getVolume() const
{
    return current_volume;
}

void SoundManager::setMusicVolume(float volume)
{
    current_volume = volume;
    SetMusicVolume(playMusic, volume);
}