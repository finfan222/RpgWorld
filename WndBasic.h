#ifndef WND_BASIC_HPP
#define WND_BASIC_HPP

#include "System.h"
#include "ResourceManager.h"

class WndBasic
{
protected:
	/// 
	/// WINDOW
	/// 
	GameScene* scene;
	String name;
	UShort width, height;
	Boolean isShown;
	vector<WndBasic> childs;

	/// 
	/// SFML
	/// 
	SFMLMusicData* theme;
	SFMLImageData* background;

public:
	WndBasic(GameScene* scene, String name, UShort width = R_800[0], UShort height = R_800[1], Boolean isShown = true);
	~WndBasic();
	/*
	Инициализация классовых ресурсов. ДОЛЖНА БЫТЬ ВЫЗЫВАНА ПОСЛЕ СОЗДАНИЯ КЛАССА НАСЛЕДНИКА!
	Плохо, но пока не придумал как это нормально и красиво вывести
	*/
	virtual void init();
	/* Титул для ImGui окна или SFML окна */
	virtual CString title();
	/* Открывает GUI окошко со всеми отрисовками */
	virtual void open(void(*Exit)());
	/* Закрывает GUI окошко со всеми отрисовками и прерывает их устанавливая isShown в false */
	virtual void close();
	/* Устанавливает переменную isShown в true */
	void show();
	/* Устанавливает переменную isShown в false */
	void hide();
	/* Отрисовывается ли окно: true, false - иначе */
	Boolean shown() const;
	/* Отдаёт name параметр GUI окна */
	String& getName();
	/* Получить все WndBasic* которые принадлежат текущему */
	vector<WndBasic> childrens();
	/* Получить окно из vector<WndBasic*> childs по его имени */
	WndBasic& childByName(String& name);
	/* Получить окно из vector<WndBasic*> которое находится последним в векторе */
	WndBasic& lastChild();
	/* Получить окно из vector<WndBasic*> которое является первым в векторе */
	WndBasic& firstChild();
	/* Подсчитать кол-во чайлдов о этого окна */
	UInt childsCount() const;
	/* Удаление чайлд-окна полным выведением его из памяти и стирая со сцены */
	void removeChild(String& name);
	/* Отрисовка SFML графики */
	virtual void redraw();
	/* Проигрывать главную тему */
	virtual void playTheme();
	Boolean isThemePlaying();
	virtual void stopTheme();

};

#endif // !WND_BASIC_HPP