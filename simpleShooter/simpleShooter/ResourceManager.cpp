#include "ResourceManager.h"

ResourceManager::ResourceManager(std::string dirName)
{
	this->everyThingIsFineBool = false;
	findResources(dirName);

	if (not this->everyThingIsFineBool) return;

	this->readConfig();

	if (not this->everyThingIsFineBool) return;

	this->parse();
	this->load();

	std::cout << "_________________" << std::endl;
	for (auto& i : everyObjectSourcePath)
	{
		std::cout << i.first;
		for (auto& j : i.second)
		{
			std::cout << std::endl;
			std::cout << j.first << std::endl;
			for (auto& k : j.second)
			{
				std::cout << k.first << " " << k.second << std::endl;
			}
		}
		std::cout << "_________________" << std::endl;
	}
}

void ResourceManager::findResources(std::string dirName)
{
	std::filesystem::path actualPath = std::filesystem::current_path();
	this->configPath = actualPath / dirName;

	std::filesystem::directory_iterator iterator = {actualPath, std::filesystem::directory_options::skip_permission_denied};
	
	for (int i = 0; i < 3; i++)
	{
		std::ranges::for_each(iterator, [&](auto& dir) {

			if (dir == configPath && dir.is_directory())
			{
				this->everyThingIsFineBool = true;
			}
			});

		if (not actualPath.has_parent_path() || this->everyThingIsFineBool == true) return;

		actualPath = actualPath.parent_path();
		iterator = { actualPath, std::filesystem::directory_options::skip_permission_denied };
		this->configPath = actualPath / dirName;
	}

}

void ResourceManager::readConfig()
{
	std::fstream inputStream;
	std::string buffer;
	std::string pathString = (this->configPath / "config.ini").string();
	inputStream.open(pathString, std::ios::in);
	if (not inputStream.is_open()) {
		this->everyThingIsFineBool = false;
		throw std::runtime_error("readConfig");
		return;
	}

	while (std::getline(inputStream, buffer))
	{
		std::ranges::for_each(buffer, [&] (char& i){
			this->rawFile.push_back(i);
			});
		this->rawFile.push_back('\n');
	}
}

void ResourceManager::parse()
{
	std::vector<std::string> halfParsedObjects;

	std::regex objectRegex(R"(\{(.*?)\})");
	std::smatch objectMatch;

	std::string::const_iterator searchStart(rawFile.cbegin());
	while (std::regex_search(searchStart, rawFile.cend(), objectMatch, objectRegex)) {
		halfParsedObjects.push_back(objectMatch[1].str());
		searchStart = objectMatch.suffix().first;
	}

	std::regex pattern(R"("([^"]+)\"\s*:\s*"([^"]+)\")");
	std::smatch keyValueMatch;

	

	for (auto& line : halfParsedObjects)
	{
		std::vector<std::string> pushToMap(4);

		//std::cout << line << std::endl;
		std::string::const_iterator searchStart(line.cbegin());
		while (std::regex_search(searchStart, line.cend(), keyValueMatch, pattern)) {
			std::string key = keyValueMatch[1].str();
			std::string value = keyValueMatch[2].str();

			if (key == "Type") pushToMap[0] = value;
			if (key == "Set") pushToMap[1] = value;
			if (key == "Name") pushToMap[2] = value;
			if (key == "Path") pushToMap[3] = value;


			//std::cout << value << std::endl;

			searchStart = keyValueMatch.suffix().first;
		}
		for (auto& a : pushToMap){
			if (a.size() == 0) throw std::runtime_error("Error. config.ini");
		}
		
		this->everyObjectSourcePath[pushToMap[0]][pushToMap[1]][pushToMap[2]] = pushToMap[3];
	}
}

void ResourceManager::load()
{
	for (auto type : everyObjectSourcePath)
	{
		if (type.first == "Texture") subLoadTexture(type.first);
		if (type.first == "Music") subLoadMusic(type.first);
		if (type.first == "Map") subLoadMap(type.first);
		if (type.first == "Font") subLoadFont(type.first);
	}
}

void ResourceManager::subLoadMap(std::string firstKey)
{
	std::string bufferPath;
	std::string bufferLine;
	std::fstream input;

	std::cout << "LOAD MAP: " << std::endl;

	for (auto& set : this->everyObjectSourcePath[firstKey])
	{
		for (auto& name : set.second)
		{
			std::cout << name.first << std::endl;
			bufferPath = (configPath / name.second).string();
			input.open(bufferPath, std::ios::in);
			if (not input.is_open()) throw std::runtime_error("maps cannot be loaded");

			while (std::getline(input, bufferLine))
			{
				this->loadedMaps[name.first].push_back(bufferLine);
			}
			input.close();
		}
	}
	/*
	for (auto& i : loadedMaps)
	{
		for (auto& j : i.second)
		{
			for (auto& k : j.second)
			{
				std::cout << k << std::endl;
			}
		}
	}
	*/
}

void ResourceManager::subLoadFont(std::string firstKey)
{
	std::string buffer;

	for (auto& set : this->everyObjectSourcePath[firstKey])
	{
		for (auto& name : set.second)
		{
			buffer = (configPath / name.second).string();
			std::cout << buffer << std::endl;
			this->loadedFonts[name.first] = std::make_shared<sf::Font>();
			if (not this->loadedFonts[name.first]->loadFromFile(buffer)) throw std::runtime_error("Font cannot be loaded " + buffer);
		}
	}
}

void ResourceManager::subLoadMusic(std::string firstKey)
{
	std::string buffer;

	for (auto& set : this->everyObjectSourcePath[firstKey])
	{
		for (auto& name : set.second)
		{
			buffer = (configPath / name.second).string();
			std::cout << buffer << std::endl;
			this->loadedMusic[set.first][name.first] = std::make_shared<sf::Music>();
			if(not this->loadedMusic[set.first][name.first]->openFromFile(buffer)) throw std::runtime_error("Music cannot be loaded " + buffer);
		}
	}
}

void ResourceManager::subLoadTexture(std::string firstKey)
{
	std::string buffer;

	for (auto& set : this->everyObjectSourcePath[firstKey])
	{
		for (auto& name : set.second)
		{
			buffer = (configPath / name.second).string();
			std::cout << buffer << std::endl;
			this->loadedTextures[set.first][name.first] = std::make_shared<sf::Texture>();
			if(not this->loadedTextures[set.first][name.first]->loadFromFile(buffer)) throw std::runtime_error("Texture cannot be loaded " + buffer);
		}
	}
}

bool ResourceManager::geteveryThingIsFineBool()
{
	return this->everyThingIsFineBool;
}

std::unordered_map<name, std::shared_ptr<sf::Texture>>& ResourceManager::getTexturesBySet(std::string set)
{
	return this->loadedTextures[set];
}

std::unordered_map<name, std::shared_ptr<sf::Music>>& ResourceManager::getMusicBySet(std::string set)
{
	return this->loadedMusic[set];
}

std::unordered_map<name, std::vector<std::string>>& ResourceManager::getMaps()
{
	return this->loadedMaps;
}

std::unordered_map<name, std::shared_ptr<sf::Font>>& ResourceManager::getFonts()
{
	return this->loadedFonts;
}


