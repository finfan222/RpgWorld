#include "ResourceManager.h"

ResourceManager* ResourceManager::instance = 0;
ResourceManagerDestroyer ResourceManager::destroyer;

ResourceManager::ResourceManager(const ResourceManager&)
{
}

ResourceManager& ResourceManager::operator=(ResourceManager&)
{
}

ResourceManager& ResourceManager::getInstance()
{
	if (!instance) {
		instance = new ResourceManager();
		destroyer.initialize(instance);
	}
	return *instance;
}

void ResourceManager::addImage(SFMLImageData* newData)
{
	String& path = *newData->path;
	String& name = *newData->name;

	// првоеряем на нахождение в памяти
	if (path.empty() || name.empty()) {
		logging::print(LogLevel::Warning, "ResourceManager::addImage(SFMLImageData* newData)", 5,
			"Can't add file: to the storage cause name or path is empty.", " Name/Path: ", name.c_str(), "/", path.c_str());
		return;
	}

	// проверяем на уже существующие fileName (не басолютные)
	if (!imageStorage.empty()) {
		vector<SFMLImageData*>::iterator it;
		for (it = imageStorage.begin(); it != imageStorage.end(); it++) {
			SFMLImageData* data = *it;
			if (strex::equalsIgnoreCase(data->getName(), name)) {
				logging::print(LogLevel::Warning, "ResourceManager::addImage(SFMLImageData* newData)", 3,
					"File with that name: ", name.c_str(), " already exists in storage. Will not be loaded.");
				return;
			}
		}
	}

	newData->texture = new sf::Texture();
	newData->sprite = new sf::Sprite();
	sf::Texture& texture = *newData->texture;
	sf::Sprite& sprite = *newData->sprite;

	// загрузка текстуры из файла и установка её в спрайт
	logging::print(LogLevel::Debug, "ResourceManager::addImage(SFMLImageData* newData)", 3,
		"Loading sprite-texture from '", path.c_str(), "'.");
	if (!texture.loadFromFile(path)) {
		throw new exception("ResourceManager loading sprite-texture resource error.");
	}
	sprite.setTexture(texture);

	imageStorage.push_back(newData);
	logging::print(LogLevel::Debug, "ResourceManager::addImage(SFMLImageData* newData)", 3,
		"SpriteTexture '", name.c_str(), "' was loaded.");

	// трансформируем картинку в зависимости от размера окна если она имеет префикс BG
	const Boolean is_background = strex::startsWith(name, "bg");
	if (is_background) {
		newData->update();
		logging::print(LogLevel::Debug, "ResourceManager::addImage(SFMLImageData* newData)", 3,
			"SpriteTexture '", name.c_str(), "' was updated for user resolution.");
	}
}

void ResourceManager::addMusic(SFMLMusicData* newData)
{
	String& path = *newData->path;
	String& name = *newData->name;
	
	// имя или путь пустые
	if (path.empty() || name.empty()) {
		logging::print(LogLevel::Warning, "ResourceManager::addMusic(SFMLMusicData* newData)", 5,
			"Can't add file: to the storage cause name or path is empty.", " Name/Path: ", name.c_str(), "/", path.c_str());
		return;
	}

	// проверяем на уже существующие fileName (не басолютные)
	if (!musicStorage.empty()) {
		vector<SFMLMusicData*>::iterator it;
		for (it = musicStorage.begin(); it != musicStorage.end(); it++) {
			SFMLMusicData* data = *it;
			if (strex::equalsIgnoreCase(data->getName(), name)) {
				logging::print(LogLevel::Warning, "ResourceManager::addMusic(SFMLMusicData* newData)", 3,
					"File with that name: ", name.c_str(), " already exists in storage. Will not be loaded.");
				return;
			}
		}
	}

	newData->music = new sf::Music();
	sf::Music& music = *newData->music;

	// загрузка текстуры из файла и установка её в спрайт
	logging::print(LogLevel::Debug, "ResourceManager::addMusic(SFMLMusicData* newData)", 2, "Loading music from path: ", path.c_str());
	if (!music.openFromFile(path)) {
		throw new exception("ResourceManager loading music resource error.");
	}

	// применяем настройки для музыки
	newData->update();

	musicStorage.push_back(newData);
	logging::print(LogLevel::Debug, "ResourceManager::addMusic(SFMLMusicData* newData)", 3, "Music file name: ", name.c_str(), " was loaded.");

	// если музыка бгшная то всегда делаем её цикличной
	const Boolean is_background = strex::startsWith(name, "bg");
	if (is_background) {
		newData->music->setLoop(true);
		logging::print(LogLevel::Debug, "ResourceManager::addMusic(SFMLMusicData* newData)", 3, "Music file '", name.c_str(), "' was setLoop=>true (cause background)");
	}
}

void ResourceManager::addSound(SFMLSoundData* newData)
{
	String& path = *newData->path;
	String& name = *newData->name;

	// имя или путь пустые
	if (path.empty() || name.empty()) {
		logging::print(LogLevel::Warning, "ResourceManager::addSound(SFMLSoundData* newData)", 5,
			"Can't add file: to the storage cause name or path is empty.", " Name/Path: ", name.c_str(), "/", path.c_str());
		return;
	}

	// проверяем на уже существующие fileName (не басолютные)
	if (!soundStorage.empty()) {
		vector<SFMLSoundData*>::iterator it;
		for (it = soundStorage.begin(); it != soundStorage.end(); it++) {
			SFMLSoundData* data = *it;
			if (strex::equalsIgnoreCase(data->getName(), name)) {
				logging::print(LogLevel::Warning, "ResourceManager::addSound(SFMLSoundData* newData)", 3,
					"File with that name: ", name.c_str(), " already exists in storage. Will not be loaded.");
				return;
			}
		}
	}

	newData->sound = new sf::Sound();
	newData->buffer = new sf::SoundBuffer();
	sf::Sound& sound = *newData->sound;
	sf::SoundBuffer& buffer = *newData->buffer;

	// применяем настройки для звука
	newData->update();

	// загрузка текстуры из файла и установка её в спрайт
	logging::print(LogLevel::Debug, "ResourceManager::addSound(SFMLSoundData* newData)", 2, "Loading sounds from path: ", path.c_str());
	if (!buffer.loadFromFile(path)) {
		throw new exception("ResourceManager loading sound resource error.");
	}
	sound.setBuffer(buffer);
	soundStorage.push_back(newData);
	logging::print(LogLevel::Debug, "ResourceManager::addSound(SFMLSoundData* newData)", 3, "Sound file name: ", name.c_str(), " was loaded.");
}

boost::optional<SFMLImageData&> ResourceManager::getImage(String name)
{
	for (int i = 0; i < imageStorage.size(); i++) {
		SFMLImageData* next = imageStorage[i];
		if (next == nullptr) {
			logging::print(LogLevel::Warning, "ResourceManager::getImage", 1, "SFMLImageData in imageStorage (foreach) has nullptr.");
			continue;
		}
		
		if(strex::equalsIgnoreCase(next->getName(), name)) {
			return *next;
		}
	}
	logging::print(LogLevel::Warning, "ResourceManager::getImage", 1, "ResourceManager::getImage Nothing to return < boost return ::none");
	return boost::none;
}

boost::optional<SFMLMusicData&> ResourceManager::getMusic(String name)
{
	for (int i = 0; i < musicStorage.size(); i++) {
		SFMLMusicData* next = musicStorage[i];
		if (next == nullptr) {
			logging::print(LogLevel::Warning, "ResourceManager::getMusic", 1, "SFMLMusicData in musicStorage (foreach) has nullptr.");
			continue;
		}

		if (strex::equalsIgnoreCase(next->getName(), name)) {
			return *next;
		}
	}
	logging::print(LogLevel::Warning, "ResourceManager::getMusic", 1, "ResourceManager::getMusic Nothing to return < boost return ::none");
	return boost::none;
}

boost::optional<SFMLSoundData&> ResourceManager::getSound(String name)
{
	for (int i = 0; i < soundStorage.size(); i++) {
		SFMLSoundData* next = soundStorage[i];
		if (next == nullptr) {
			logging::print(LogLevel::Warning, "ResourceManager::getSound", 1, "SFMLSoundData in soundStorage (foreach) has nullptr.");
			continue;
		}
		
		if (strex::equalsIgnoreCase(next->getName(), name)) {
			return *next;
		}
	}

	logging::print(LogLevel::Warning, "ResourceManager::getSound", 1, "ResourceManager::getSound Nothing to return < boost return ::none");
	return boost::none;
}

void ResourceManager::loadImages(GameScene* scene)
{
	try {
		for (const auto& next : boost::filesystem::directory_iterator("./images/")) {
			RESOURCE_MANAGER_API.addImage(new SFMLImageData(next.path().string(), *scene));
		}
	}
	catch (exception e) {
		logging::print(e);
	}
}

void ResourceManager::loadMusic()
{
	try {
		for (const auto& next : boost::filesystem::directory_iterator("./music/")) {
			RESOURCE_MANAGER_API.addMusic(new SFMLMusicData(next.path().string()));
		}
	}
	catch (exception e) {
		logging::print(e);
	}
}

void ResourceManager::loadSounds()
{
	try {
		for (const auto& next : boost::filesystem::directory_iterator("./sounds/")) {
			RESOURCE_MANAGER_API.addSound(new SFMLSoundData(next.path().string()));
		}
	}
	catch (exception e) {
		logging::print(e);
	}
}

ResourceManagerDestroyer::~ResourceManagerDestroyer()
{
	delete instance;
}

void ResourceManagerDestroyer::initialize(ResourceManager* instance)
{
	this->instance = instance;
}