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
	������������� ��������� ��������. ������ ���� �������� ����� �������� ������ ����������!
	�����, �� ���� �� �������� ��� ��� ��������� � ������� �������
	*/
	virtual void init();
	/* ����� ��� ImGui ���� ��� SFML ���� */
	virtual CString title();
	/* ��������� GUI ������ �� ����� ����������� */
	virtual void open(void(*Exit)());
	/* ��������� GUI ������ �� ����� ����������� � ��������� �� ������������ isShown � false */
	virtual void close();
	/* ������������� ���������� isShown � true */
	void show();
	/* ������������� ���������� isShown � false */
	void hide();
	/* �������������� �� ����: true, false - ����� */
	Boolean shown() const;
	/* ����� name �������� GUI ���� */
	String& getName();
	/* �������� ��� WndBasic* ������� ����������� �������� */
	vector<WndBasic> childrens();
	/* �������� ���� �� vector<WndBasic*> childs �� ��� ����� */
	WndBasic& childByName(String& name);
	/* �������� ���� �� vector<WndBasic*> ������� ��������� ��������� � ������� */
	WndBasic& lastChild();
	/* �������� ���� �� vector<WndBasic*> ������� �������� ������ � ������� */
	WndBasic& firstChild();
	/* ���������� ���-�� ������� � ����� ���� */
	UInt childsCount() const;
	/* �������� �����-���� ������ ���������� ��� �� ������ � ������ �� ����� */
	void removeChild(String& name);
	/* ��������� SFML ������� */
	virtual void redraw();
	/* ����������� ������� ���� */
	virtual void playTheme();
	Boolean isThemePlaying();
	virtual void stopTheme();

};

#endif // !WND_BASIC_HPP