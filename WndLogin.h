#ifndef WND_LOGIN_HPP
#define WND_LOGIN_HPP

#include "WndBasic.h"
#include "NetworkService.h"
#include "ResourceManager.h"

class WndLogin : public WndBasic
{
private:
    char InputLoginTextBuffer[16] = { 0 };
    char InputPasswordTextBuffer[16] = { 0 };
    const UShort LoginAreaColumns = 2;
    NetworkService& network;
    void createInputArea();
    void createButtonArea(void(*Exit)());

public:
    WndLogin(NetworkService& network, GameScene* scene, String name, UShort width, UShort height, Boolean isShown = true);
    ~WndLogin();
    CString title();
    void open(void(*Exit)()) override;
    void close() override;
    void redraw() override;
    void init() override;
};

#endif // !WND_LOGIN_HPP