#include "WndBasic.h"

WndBasic::WndBasic(GameScene* scene, String name, UShort width, UShort height, Boolean isShown)
	: scene(scene), name(name), width(width), height(height),
	isShown(isShown), background(nullptr), theme(nullptr)
{
	logging::print(LogLevel::Debug, "WndBasic::WndBasic", 7,
		name, ": ",
		to_string(width),
		"x",
		to_string(height),
		" is shown: ",
		to_string(isShown));
}

WndBasic::~WndBasic()
{
}

void WndBasic::open(void(*Exit)())
{
	show();
}

void WndBasic::close()
{
	hide();
}

void WndBasic::show()
{
	isShown = true;
}

void WndBasic::hide()
{
	isShown = false;
}

Boolean WndBasic::shown() const
{
	return isShown;
}

void WndBasic::init()
{
}

String& WndBasic::getName()
{
	return name;
}

vector<WndBasic> WndBasic::childrens()
{
	return childs;
}

WndBasic& WndBasic::childByName(String& name)
{
	for (int i = 0; i < childs.size(); i++) {
		WndBasic& nextChild = childs[i];
		if (strex::equalsIgnoreCase(nextChild.getName(), name)) {
			return nextChild;
		}
	}
	return firstChild();
}

WndBasic& WndBasic::lastChild()
{
	return childs[childs.size() - 1];
}

WndBasic& WndBasic::firstChild()
{
	return childs[0];
}

UInt WndBasic::childsCount() const
{
	return static_cast<UInt>(childs.size());
}

void WndBasic::removeChild(String& name)
{
	vector<WndBasic>::iterator it;
	for (it = childs.begin(); it != childs.end(); it++) {
		if (it->getName().empty()) {
			return;
		}
	}
}

void WndBasic::redraw()
{
}

Boolean WndBasic::isThemePlaying()
{
	if (theme == nullptr) {
		cerr << "Theme is null ptr in WndBasic::isThemePlaying" << endl;
		return false;
	}
	return theme->is(sf::Music::Status::Playing);
}

void WndBasic::stopTheme()
{
	if (theme == nullptr) {
		return;
	}
	theme->music->stop();
}

void WndBasic::addChild(WndBasic* wnd)
{
	childs.push_back(*wnd);
}

void WndBasic::playTheme()
{
	if (theme == nullptr) {
		cerr << "Theme is nullptr in WndBasic::playTheme" << endl;
		return;
	}

	theme->music->play();
}

CString WndBasic::title() {
	return "Unknown";
}