#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include "System.h"

class ResourceManager;

#ifndef RESOURCE_MANAGER_API
#define RESOURCE_MANAGER_API	ResourceManager::getInstance()
#endif

class ResourceManagerDestroyer
{
private:
	ResourceManager* instance;
public:
	~ResourceManagerDestroyer();
	void initialize(ResourceManager* instance);
};

class ResourceManager
{
private:
	static ResourceManager* instance;
	static ResourceManagerDestroyer destroyer;
	vector<SFMLImageData*> imageStorage;
	vector<SFMLMusicData*> musicStorage;
	vector<SFMLSoundData*> soundStorage;
	void addImage(SFMLImageData* newData);
	void addMusic(SFMLMusicData* newData);
	void addSound(SFMLSoundData* newData);

protected:
	ResourceManager() {}
	ResourceManager(const ResourceManager&);
	ResourceManager& operator=(ResourceManager&);
	~ResourceManager() {}
	friend class ResourceManagerDestroyer;

public:
	static ResourceManager& getInstance();
	boost::optional<SFMLImageData&> getImage(String name);
	boost::optional<SFMLMusicData&> getMusic(String name);
	boost::optional<SFMLSoundData&> getSound(String name);
	void loadImages(GameScene* scene);
	void loadMusic();
	void loadSounds();
};

#endif // !RESOURCE_MANAGER_HPP