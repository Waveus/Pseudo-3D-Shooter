#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <filesystem>
#include <regex>
#include <unordered_map>
#include <iostream>
#include <ranges>
#include <algorithm>
#include <thread>
#include <fstream>
#include <sstream>
#include <mutex>

using set = std::string;
using type = std::string;
using path = std::string;
using name = std::string;

class ResourceManager
{
private:
	std::filesystem::path configPath;

	std::unordered_map<type, std::unordered_map<set, std::unordered_map<name, path>>> everyObjectSourcePath;
	std::unordered_map<set, std::unordered_map<name, std::shared_ptr<sf::Music>>> loadedMusic;
	std::unordered_map<set, std::unordered_map<name, std::shared_ptr<sf::Texture>>> loadedTextures;
	std::unordered_map<name, std::shared_ptr<sf::Font>> loadedFonts;
	std::unordered_map<name, std::vector<std::string>> loadedMaps;

	std::string rawFile;

	bool everyThingIsFineBool;

	std::mutex lock;

	void findResources(std::string dirName);
	void readConfig();

	void parse();
	
	void load();

	void subLoadMap(std::string firstKey); //TODO: rearrage it!!!
	void subLoadFont(std::string firstKey); //TODO: rearrage it!!!
	void subLoadMusic(std::string firstKey);
	void subLoadTexture(std::string firstKey); 
public:
	ResourceManager(std::string dirName);

	std::unordered_map<name, std::shared_ptr<sf::Texture>>& getTexturesBySet(std::string set);
	std::unordered_map<name, std::shared_ptr<sf::Music>>& getMusicBySet(std::string set);
	std::unordered_map<name, std::vector<std::string>>& getMaps();
	std::unordered_map<name, std::shared_ptr<sf::Font>>& getFonts();

	bool geteveryThingIsFineBool();
};

