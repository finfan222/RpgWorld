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
		cerr << "Wrong path or name." << endl;
		return;
	}

	// проверяем на уже существующие fileName (не басолютные)
	if (!imageStorage.empty()) {
		vector<SFMLImageData*>::iterator it;
		for (it = imageStorage.begin(); it != imageStorage.end(); it++) {
			SFMLImageData* data = *it;
			if (strex::equalsIgnoreCase(data->getName(), name)) {
				cerr << "Image file with name '" << name << "' already exists in storage." << endl;
				return;
			}
		}
	}

	newData->texture = new sf::Texture();
	newData->sprite = new sf::Sprite();
	sf::Texture& texture = *newData->texture;
	sf::Sprite& sprite = *newData->sprite;

	// загрузка текстуры из файла и установка её в спрайт
	cout << "Loading image from path: " << path << endl;
	if (!texture.loadFromFile(path)) {
		cerr << "Image file '" << path << "' not found!" << endl;
		throw new exception("ResourceManager loading resource error.");
	}
	sprite.setTexture(texture);

	cout << "Image file: " << name << endl;
	imageStorage.push_back(newData);
	cout << "Image '" << name << "' was added." << endl;

	// трансформируем картинку в зависимости от размера окна если она имеет префикс BG
	const Boolean is_background = strex::startsWith(name, "bg");
	if (is_background) {
		newData->update();
		cout << name << " was transformed to new size (windowed size)." << endl;
	}
}

void ResourceManager::addMusic(SFMLMusicData* newData)
{
	String& path = *newData->path;
	String& name = *newData->name;
	
	// првоеряем на нахождение в памяти
	if (path.empty() || name.empty()) {
		cerr << "Wrong path or name." << endl;
		return;
	}

	// проверяем на уже существующие fileName (не басолютные)
	if (!musicStorage.empty()) {
		vector<SFMLMusicData*>::iterator it;
		for (it = musicStorage.begin(); it != musicStorage.end(); it++) {
			SFMLMusicData* data = *it;
			if (strex::equalsIgnoreCase(data->getName(), name)) {
				cerr << "Music file with name '" << name << "' already exists in storage." << endl;
				return;
			}
		}
	}

	newData->music = new sf::Music();
	sf::Music& music = *newData->music;

	// загрузка текстуры из файла и установка её в спрайт
	cout << "Loading music from path: " << path << endl;
	if (!music.openFromFile(path)) {
		cerr << "Music file '" << path << "' not found!" << endl;
		throw new exception("ResourceManager loading resource error.");
	}

	cout << "Music file name: " << name << endl;
	musicStorage.push_back(newData);
	cout << "Music '" << name << "' was added." << endl;

	// если музыка бгшная то всегда делаем её цикличной
	const Boolean is_background = strex::startsWith(name, "bg");
	if (is_background) {
		newData->music->setLoop(true);
	}
}

boost::optional<SFMLImageData&> ResourceManager::getImage(String name)
{
	for (int i = 0; i < imageStorage.size(); i++) {
		SFMLImageData* next = imageStorage[i];
		if (next == nullptr) {
			cerr << "index " << i << " has nullptr." << endl;
		} else if(strex::equalsIgnoreCase(next->getName(), name)) {
			return *next;
		}
	}
	return boost::none;
}

boost::optional<SFMLMusicData&> ResourceManager::getMusic(String name)
{
	for (int i = 0; i < musicStorage.size(); i++) {
		SFMLMusicData* next = musicStorage[i];
		if (next == nullptr) {
			cerr << "index " << i << " has nullptr." << endl;
		}
		else if (strex::equalsIgnoreCase(next->getName(), name)) {
			return *next;
		}
	}
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
		cerr << "ErrorImageLoading: " << e.what() << endl;
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
		cerr << "ErrorMusicLoading: " << e.what() << endl;
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