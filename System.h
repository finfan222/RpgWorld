#ifndef SYSTEM_HPP
#define SYSTEM_HPP

// System imports
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <map>
#include <vector>
#include <type_traits>
#include <list>
#include <cstdarg>
#include <WinSock2.h>
#include <iomanip>
#include <codecvt>
#include <cstddef>
#include <bitset>
#include <algorithm>

// Boost imports
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/container/list.hpp>
#include <boost/optional.hpp>
#include <boost/filesystem.hpp>

// SFML imports
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

// Im Gui imports
#include "imgui.h"
#include "imgui-SFML.h"

// Project .h
#include "Enums.h"

using namespace std;

/////////////////////// TYPE DEFINES
typedef int16_t Short;
typedef int32_t Int;
typedef int64_t Long;
typedef uint16_t UShort;
typedef uint32_t UInt;
typedef uint64_t ULong;
typedef double_t Double;
typedef float_t Float;
typedef string String;
typedef const char* CString;
typedef char Character;
typedef byte Bytes;
typedef bool Boolean;
typedef bool* CBoolean;
typedef char ByteBuffer1024[1024];
typedef char ByteBuffer2048[1024 * 2];
typedef char ByteBuffer4096[1024 * 4];
typedef char ByteBuffer8192[1024 * 8];
/////////////////////// SFML
typedef sf::RenderWindow GameScene;
typedef sf::Music::Status MusicStatus;

#define CLOSEABLE					CBoolean(true)
#define NON_CLOSEABLE				CBoolean(false)
#define PNG_EXT						".png"
#define OGG_EXT						".ogg"
#define WAV_EXT						".wav"

#define GAME_NAME					"Alden World"

// Login Window
#define ID_LOGIN_AREA				"Login"
#define ID_LOGIN_AREA_INPUT			"Login_Input"
#define ID_LOGIN_AREA_BUTTONS		"Login_Buttons"
#define ID_LOGIN_AREA_OPTIONS		"Login_Options" // fixme: implementation

// Inventory Window
#define ID_INVENTORY_AREA			"Inventory"
#define ID_INVENTORY_AREA_TABLE		"Inventory_Table"
#define ID_INVENTORY_AREA_WIDTH		288
#define ID_INVENTORY_AREA_HEIGHT	320
#define ID_INVENTORY_ITEM_SIZE		32
#define ID_INVENTORY_COLUMNS		(ID_INVENTORY_AREA_WIDTH / ID_INVENTORY_ITEM_SIZE - 2)
#define ID_INVENTORY_ROWS			(ID_INVENTORY_AREA_HEIGHT / ID_INVENTORY_ITEM_SIZE)

/////////////////////// CONFIGURATIONS
static UShort WindowResolutions[5][2] = {
	{640,480},
	{800,600},
	{1024,768},
	{1600,900},
	{1920,1080}
};

#define R_640	WindowResolutions[0]
#define R_800	WindowResolutions[1]
#define R_1024	WindowResolutions[2]
#define R_1600	WindowResolutions[3]
#define R_1920	WindowResolutions[4]

template <typename E> constexpr auto cast(E e) noexcept {
	return static_cast<std::underlying_type_t<E>>(e);
}

/////////////////////// NAMESPACES
namespace conf {
	static UShort* WINDOW_RESOLUTION = WindowResolutions[1];
	static String LANGUAGE = "en";
};

namespace ctrlex {
	/*sf::Keyboard::Key W = sf::Keyboard::W;
	sf::Keyboard::Key UP = sf::Keyboard::Up;
	sf::Keyboard::Key S = sf::Keyboard::S;
	sf::Keyboard::Key D = sf::Keyboard::A;
	sf::Keyboard::Key A = sf::Keyboard::D;
	sf::Keyboard::Key Enter = sf::Keyboard::Enter;
	sf::Keyboard::Key Backspace = sf::Keyboard::Backspace;
	sf::Keyboard::Key Esc = sf::Keyboard::Escape;*/
}

namespace strex {
	String& toLowerCase(String& text);
	String& toUpperCase(String& text);
	vector<String> split(String& text, String delim);
	const Boolean contains(String& text, String value, Boolean ignoreCase = true);
	const Boolean endsWith(String& text, String value, Boolean ignoreCase = true);
	const Boolean startsWith(String& text, String value, Boolean ignoreCase = true);
	const Int size(String& text);
	const Boolean equalsIgnoreCase(String text, String findout);
	const Boolean equals(String& text, String& findout);
	String& replace(String& text, String from, String to);
	const Boolean isEmpty(String& text);
	String& removeAllWords(String& text, String& word);
	const Short toShort(String& text, Boolean u = true);
	const Long toLong(String& text, Boolean u = true);
	const Int toInt(String& text, Boolean u = true);
	const Double toDouble(String& text);
	const Float toFloat(String& text);
	const Boolean toBool(String& text);
}

namespace wndflag {
	static UInt Unscroll = ImGuiWindowFlags_NoScrollbar;
	static UInt Unmove = ImGuiWindowFlags_NoMove;
	static UInt Untitle = ImGuiWindowFlags_NoTitleBar;
	static UInt Unresize = ImGuiWindowFlags_NoResize;
	static UInt Uncollapse = ImGuiWindowFlags_NoCollapse;
}

namespace tabflag {
	static UInt Bordered = ImGuiTableFlags_Borders;
	static UInt None = ImGuiTableFlags_None;
	static UInt Resizable = ImGuiTableFlags_Resizable;
	static UInt Reorderable = ImGuiTableFlags_Reorderable;
	static UInt Hideable = ImGuiTableFlags_Hideable;
	static UInt Sortable = ImGuiTableFlags_Sortable;
	static UInt NoSavedSettings = ImGuiTableFlags_NoSavedSettings;
	static UInt ContextMenuInBody = ImGuiTableFlags_ContextMenuInBody;
	static UInt RowBg = ImGuiTableFlags_RowBg;
	static UInt BordersInnerH = ImGuiTableFlags_BordersInnerH;
	static UInt BordersOuterH = ImGuiTableFlags_BordersOuterH;
	static UInt BordersInnerV = ImGuiTableFlags_BordersInnerV;
	static UInt BordersOuterV = ImGuiTableFlags_BordersOuterV;
	static UInt BordersH = ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_BordersOuterH;
	static UInt BordersV = ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersOuterV;
	static UInt BordersInner = ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersInnerH;
	static UInt BordersOuter = ImGuiTableFlags_BordersOuterV | ImGuiTableFlags_BordersOuterH;
	static UInt Borders = ImGuiTableFlags_BordersInner | ImGuiTableFlags_BordersOuter;
	static UInt NoBordersInBody = ImGuiTableFlags_NoBordersInBody;
	static UInt NoBordersInBodyUntilResize = ImGuiTableFlags_NoBordersInBodyUntilResize;
	static UInt SizingFixedFit = ImGuiTableFlags_SizingFixedFit;
	static UInt SizingFixedSame = ImGuiTableFlags_SizingFixedSame;
	static UInt SizingStretchProp = ImGuiTableFlags_SizingStretchProp;
	static UInt SizingStretchSame = ImGuiTableFlags_SizingStretchSame;
	static UInt NoHostExtendX = ImGuiTableFlags_NoHostExtendX;
	static UInt NoHostExtendY = ImGuiTableFlags_NoHostExtendY;
	static UInt NoKeepColumnsVisible = ImGuiTableFlags_NoKeepColumnsVisible;
	static UInt PreciseWidths = ImGuiTableFlags_PreciseWidths;
	static UInt NoClip = ImGuiTableFlags_NoClip;
	static UInt PadOuterX = ImGuiTableFlags_PadOuterX;
	static UInt NoPadOuterX = ImGuiTableFlags_NoPadOuterX;
	static UInt NoPadInnerX = ImGuiTableFlags_NoPadInnerX;
	static UInt ScrollX = ImGuiTableFlags_ScrollX;
	static UInt ScrollY = ImGuiTableFlags_ScrollY;
	static UInt SortMulti = ImGuiTableFlags_SortMulti;
	static UInt SortTristate = ImGuiTableFlags_SortTristate;
}

namespace intxtflag {
	static UInt None = ImGuiInputTextFlags_None;
	/* Можно вводить 0-9.+- */
	static UInt Decimal = ImGuiInputTextFlags_CharsDecimal;
	/* Можно вводить 0123456789ABCDEFabcdef */
	static UInt Hexadecimal = ImGuiInputTextFlags_CharsHexadecimal;
	/* Превращает нижний регистр в верхний (всё что введено) */
	static UInt Uppercase = ImGuiInputTextFlags_CharsUppercase;
	/* Не позволяет ставить пробелы, табуляции и т.д. */
	static UInt NoBlank = ImGuiInputTextFlags_CharsNoBlank;
	/* При вводе - автоматически выделяется весь текст */
	static UInt AutoSelectAll = ImGuiInputTextFlags_AutoSelectAll;
	/* Обработка enter включена */
	static UInt EnterReturnsTrue = ImGuiInputTextFlags_EnterReturnsTrue;
	/* Вызывает авто-комплит текста? */
	static UInt CallbackCompletion = ImGuiInputTextFlags_CallbackCompletion;
	/* Стрелки вверх и вниз - позволяют ходить по истории ввода (ранее введённый текст) */
	static UInt CallbackHistory = ImGuiInputTextFlags_CallbackHistory;
	/* Коллбэк при каждом инпуте (вводе символа) */
	static UInt CallbackAlways = ImGuiInputTextFlags_CallbackAlways;
	static UInt CallbackCharFilter = ImGuiInputTextFlags_CallbackCharFilter;
	/* Нажатие tab вводит в inputText '\t' */
	static UInt AllowTabInput = ImGuiInputTextFlags_AllowTabInput;
	/* Для мультилайнов: позволяет нажатием enter переходить на след. строку */
	static UInt CtrlEnterForNewLine = ImGuiInputTextFlags_CtrlEnterForNewLine;
	/* Запрещает курсору прокручиваться горизонтально (влево/вправо) */
	static UInt NoHorizontalScroll = ImGuiInputTextFlags_NoHorizontalScroll;
	/* Перезапись текущего текста: работает как insert? */
	static UInt AlwaysOverwrite = ImGuiInputTextFlags_AlwaysOverwrite;
	/* Только чтение. Редактировать текст внутри поля - невозможно. */
	static UInt ReadOnly = ImGuiInputTextFlags_ReadOnly;
	/* При вводе символов в поле, вместо их отображения будет: "*******" */
	static UInt Password = ImGuiInputTextFlags_Password;
	/* Запрещает Ctrl+V, Ctrl+C для поля (т.е. ничего не вставим туда из буфера и не скопируем оттуда в буфер) */
	static UInt NoUndoRedo = ImGuiInputTextFlags_NoUndoRedo;
	/* Позволяет вводить 0123456789.+-*\/eE */
	static UInt CharsScientific = ImGuiInputTextFlags_CharsScientific;
	/* Resize поля: // Callback on buffer capacity changes request (beyond 'buf_size' parameter value),
	allowing the string to grow. Notify when the string wants to be resized (for string types which hold a cache of their Size). 
	You will be provided a new BufSize in the callback and NEED to honor it. (see misc/cpp/imgui_stdlib.h for an example of using this) */
	static UInt CallbackResize = ImGuiInputTextFlags_CallbackResize;
	/* Колбэк во время textEditing: Callback on any edit (note that InputText() already returns true on edit,
	the callback is useful mainly to manipulate the underlying buffer while focus is active)*/
	static UInt CallbackEdit = ImGuiInputTextFlags_CallbackEdit;
	/* ESC очищает всё inputText поле */
	static UInt EscapeClearsAll = ImGuiInputTextFlags_EscapeClearsAll;
	/* Шаблон для inputText: пароль */
	static UInt TemplatePassword = NoHorizontalScroll | NoUndoRedo | Password | Hexadecimal | NoBlank | EnterReturnsTrue | EscapeClearsAll;
	/* Шаблон для inputText: любой текст */
	static UInt TemplateText = Hexadecimal | EnterReturnsTrue | EscapeClearsAll;
}

struct SFMLImageData {
	GameScene* scene;
	String* path;
	String* name;
	sf::Texture* texture;
	sf::Sprite* sprite;
	SFMLImageData(String fullPath, GameScene& scene);
	~SFMLImageData();
	String& getName();
	void update();
};

struct SFMLMusicData {
	String* path;
	String* name;
	sf::Music* music;
	SFMLMusicData(String fullPath);
	~SFMLMusicData();
	String& getName();
	Boolean is(MusicStatus status);
};

struct SFMLSoundData {
	String* path;
	String* name;
	sf::SoundBuffer* buffer;
	sf::Sound* sound;
	SFMLSoundData(String fullPath);
	~SFMLSoundData();
	String& getName();
};

#endif