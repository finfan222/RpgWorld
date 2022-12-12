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

	// ��������� ����������
	if (!strex::endsWith(fullPath, PNG_EXT)) {
		throw exception("SFMLImageData extension error.");
	}

	// ��������� ����������� ���� � �����
	path = new String(fullPath);

	// ��������� ����� ����� ��� [.ext] � ��� [path/subpath/] ��������
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
	logging::print(LogLevel::Debug, "SFMLImageData::update()", 3, "Image '", name->c_str(), "' updated.");
	sf::Vector2u vec = scene->getSize();
	sf::Vector2u vec2 = texture->getSize();
	Float x1 = static_cast<float>(vec.x) / static_cast<float>(vec2.x);
	Float y1 = static_cast<float>(vec.y) / static_cast<float>(vec2.y);
	sprite->setScale(sf::Vector2f(x1, y1));
}

SFMLMusicData::SFMLMusicData(String fullPath)
{
	// ��������� ����������
	if (!strex::endsWith(fullPath, OGG_EXT)) {
		throw exception("SFMLMusicData extension error.");
	}

	// ��������� ����������� ���� � �����
	path = new String(fullPath);

	// ��������� ����� ����� ��� [.ext] � ��� [path/subpath/] ��������
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

void SFMLMusicData::update()
{
	music->setVolume(conf::MUSIC_VOLUME);
}

SFMLSoundData::SFMLSoundData(String fullPath)
{
	// ��������� ����������
	if (!strex::endsWith(fullPath, WAV_EXT)) {
		throw exception("SFMLSoundData extension error.");
	}

	// ��������� ����������� ���� � �����
	path = new String(fullPath);

	// ��������� ����� ����� ��� [.ext] � ��� [path/subpath/] ��������
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

void SFMLSoundData::play()
{
	try {
		sound->play();
	}
	catch (exception e) {
		cerr << e.what() << endl;
	}
}

void SFMLSoundData::update()
{
	sound->setVolume(conf::SOUND_VOLUME);
}

Boolean gui::button(CString title, ImVec2 size)
{
	if (ImGui::Button(title, size)) {
		RESOURCE_MANAGER_API.getSound("click").value().play();
		return true;
	}
	return false;
}

void logging::print(LogLevel level, CString from, UInt cnt, ...)
{
	try {
		String output = "";
		if (level == LogLevel::Error) {
			output.append("ERROR ");
		}
		else if (level == LogLevel::Warning) {
			output.append("WARNING ");
		}
		else {
			output.append("DEBUG ");
		}

		time_t t = time(nullptr);
		String format(20, 0);
		format.resize(strftime(&format[0], format.size(), "%d.%m.%Y %I:%M:%S", localtime(&t)));
		output.append(format).append(" ");

		// ������ (����� ��� �������)
		output.append(from).append(": ");

		va_list args;
		va_start(args, cnt);
		for (int i = 0; i < cnt; i++) {
			const char* t = va_arg(args, const char*);
			output.append(String(t));
		}
		va_end(args);

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if (level == LogLevel::Error) {
			SetConsoleTextAttribute(hConsole, 12);
			cerr << output << endl;
			SetConsoleTextAttribute(hConsole, 7);
		}
		else if (level == LogLevel::Warning) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
			cerr << output << endl;
			SetConsoleTextAttribute(hConsole, 7);
		}
		else {
			SetConsoleTextAttribute(hConsole, 2);
			cout << output << endl;
			SetConsoleTextAttribute(hConsole, 7);
		}
	}
	catch (exception e) {
		logging::print(e);
	}
}

void logging::print(exception e)
{
	String output = "ERROR ";
	time_t t = time(nullptr);
	String format(20, 0);
	format.resize(strftime(&format[0], format.size(), "%d.%m.%Y %I:%M:%S", localtime(&t)));
	output.append(format).append(" ");
	output.append(e.what());
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	cerr << output << endl;
	SetConsoleTextAttribute(hConsole, 7);
}
