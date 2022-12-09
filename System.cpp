#include "System.h"
#include "ResourceManager.h"

String& strex::toLowerCase(String& text)
{
	boost::algorithm::to_lower(text);
	return text;
}

String& strex::toUpperCase(String& text)
{
	boost::algorithm::to_upper(text);
	return text;
}

vector<String> strex::split(String& text, String delim)
{
	vector<String> temp;
	return boost::split(temp, text, boost::is_any_of(delim));
}

const Boolean strex::contains(String& text, String value, Boolean ignoreCase)
{
	if (ignoreCase) {
		String temp = String(text);
		toLowerCase(temp);
		toLowerCase(value);
		return temp.find(value) != String::npos;
	}
	return text.find(value) != String::npos;
}

const Boolean strex::endsWith(String& text, String value, Boolean ignoreCase)
{
	if (ignoreCase) {
		String temp = String(text);
		toLowerCase(temp);
		toLowerCase(value);
		return boost::ends_with(text, value);
	}
	return boost::ends_with(text, value);
}

const Boolean strex::startsWith(String& text, String value, Boolean ignoreCase)
{
	if (ignoreCase) {
		String temp = String(text);
		toLowerCase(temp);
		toLowerCase(value);
		return boost::starts_with(text, value);
	}
	return boost::starts_with(text, value);
}

const Int strex::size(String& text)
{
	return static_cast<UInt>(text.length());
}

const Boolean strex::equalsIgnoreCase(String text, String findout)
{
	return boost::iequals(text, findout);
}

const Boolean strex::equals(String& text, String& findout)
{
	return boost::equals(text, findout);
}

String& strex::replace(String& text, String from, String to)
{
	boost::replace_all(text, from, to);
	return text;
}

const Boolean strex::isEmpty(String& text)
{
	return text.empty();
}

String& strex::removeAllWords(String& text, String& word)
{
	return !isEmpty(text) ? replace(text, word, "") : text;
}

const Short strex::toShort(String& text, Boolean u)
{
	return u ? boost::lexical_cast<UShort>(text) : boost::lexical_cast<Short>(text);
}

const Long strex::toLong(String& text, Boolean u)
{
	return u ? boost::lexical_cast<ULong>(text) : boost::lexical_cast<Long>(text);
}

const Int strex::toInt(String& text, Boolean u)
{
	return u ? boost::lexical_cast<UInt>(text) : boost::lexical_cast<Int>(text);
}

const Double strex::toDouble(String& text)
{
	return boost::lexical_cast<Double>(text);
}

const Float strex::toFloat(String& text)
{
	return boost::lexical_cast<Float>(text);
}

const Boolean strex::toBool(String& text)
{
	return boost::lexical_cast<Boolean>(equalsIgnoreCase(text, "true") ? true : false);
}

//////////////////////////////////// SFML Structures
SFMLImageData::SFMLImageData(String fullPath, GameScene& scene)
{
	this->scene = &scene;

	// проверяем расширение
	if (!strex::endsWith(fullPath, PNG_EXT)) {
		throw exception("SFMLImageData extension error.");
	}

	// установка абсолютного пути к файлу
	path = new String(fullPath);

	// установка имени файла без [.ext] и без [path/subpath/] символов
	vector<String> splitter = strex::split(strex::replace(fullPath, PNG_EXT, ""), "/");
	name = new String(splitter[splitter.size() - 1]);
}

SFMLImageData::~SFMLImageData()
{
	delete texture, sprite, path, name;
}

String& SFMLImageData::getName()
{
	return *name;
}

void SFMLImageData::update()
{
	cout << "update image..." << *name << endl;
	sf::Vector2u vec = scene->getSize();
	sf::Vector2u vec2 = texture->getSize();
	Float x1 = static_cast<float>(vec.x) / static_cast<float>(vec2.x);
	Float y1 = static_cast<float>(vec.y) / static_cast<float>(vec2.y);
	sprite->setScale(sf::Vector2f(x1, y1));
}

SFMLMusicData::SFMLMusicData(String fullPath)
{
	// проверяем расширение
	if (!strex::endsWith(fullPath, OGG_EXT)) {
		throw exception("SFMLMusicData extension error.");
	}

	// установка абсолютного пути к файлу
	path = new String(fullPath);

	// установка имени файла без [.ext] и без [path/subpath/] символов
	vector<String> splitter = strex::split(strex::replace(fullPath, OGG_EXT, ""), "/");
	name = new String(splitter[splitter.size() - 1]);
}

SFMLMusicData::~SFMLMusicData()
{
	delete path, name, music;
}

String& SFMLMusicData::getName()
{
	return *name;
}

Boolean SFMLMusicData::is(MusicStatus status)
{
	return music->getStatus() == status;
}

SFMLSoundData::SFMLSoundData(String fullPath)
{
	// проверяем расширение
	if (!strex::endsWith(fullPath, WAV_EXT)) {
		throw exception("SFMLSoundData extension error.");
	}

	// установка абсолютного пути к файлу
	path = new String(fullPath);

	// установка имени файла без [.ext] и без [path/subpath/] символов
	vector<String> splitter = strex::split(strex::replace(fullPath, WAV_EXT, ""), "/");
	name = new String(splitter[splitter.size() - 1]);
}

SFMLSoundData::~SFMLSoundData()
{
	delete path, name, buffer, sound;
}

String& SFMLSoundData::getName()
{
	return *name;
}
