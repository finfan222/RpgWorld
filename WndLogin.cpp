#include "WndLogin.h"

void WndLogin::redraw()
{
    scene->draw(*background->sprite);
}

void WndLogin::init()
{
    background = &RESOURCE_MANAGER_API.getImage("bg_login").value();
    theme = &RESOURCE_MANAGER_API.getMusic("bg_login").value();
}

void WndLogin::createInputArea()
{
    if (ImGui::BeginTable(ID_LOGIN_AREA_INPUT, LoginAreaColumns, tabflag::SizingFixedFit)) {
        // login
        ImGui::TableNextRow();
        {
            if (ImGui::TableSetColumnIndex(0)) {
                ImGui::PushItemWidth(32);
                ImGui::Text("Login:");
                ImGui::PopItemWidth();
            }

            if (ImGui::TableSetColumnIndex(1)) {
                ImGui::SetNextItemWidth(128);
                ImGui::PushItemWidth(-1);
                ImGui::InputText("login_input_area", InputLoginTextBuffer, IM_ARRAYSIZE(InputLoginTextBuffer), intxtflag::TemplateText);
                ImGui::PopItemWidth();
            }
        }
        // password
        ImGui::TableNextRow();
        {
            if (ImGui::TableSetColumnIndex(0)) {
                ImGui::PushItemWidth(32);
                ImGui::Text("PWD:");
                ImGui::PopItemWidth();
            }

            if (ImGui::TableSetColumnIndex(1)) {
                ImGui::PushItemWidth(-1);
                ImGui::InputText("password_input_area", InputPasswordTextBuffer, IM_ARRAYSIZE(InputPasswordTextBuffer), intxtflag::TemplatePassword);
                ImGui::PopItemWidth();
            }
        }
        ImGui::EndTable();
    }
}

void WndLogin::createButtonArea(void(*Exit)())
{
    if (ImGui::BeginTable(ID_LOGIN_AREA_BUTTONS, LoginAreaColumns, tabflag::SizingFixedFit)) {
        ImGui::Indent(20);
        ImGui::TableNextRow();
        {
            static ImVec2 ButtonSize(64, 21);
            {
                // button Log-In
                if (ImGui::TableSetColumnIndex(0)) {
                    if (ImGui::Button("Log-In", ButtonSize)) {
                        RequestLogin info;
                        info.login = InputLoginTextBuffer;
                        info.password = InputPasswordTextBuffer;
                        if (!info.validate()) {
                            cerr << "Wrong login or password info, try again!" << endl;
                            return;
                        }
                        cout << "Send to server: " << endl;
                        cout << "> login=" << info.login << endl;
                        cout << "> password=" << info.password << endl;
                        if (network.tryConnect()) {
                            // fixme: test connect
                            VersionRequest test;
                            test.version = 1;
                            sendPacket(test);
                            receivePacket();
                        }
                        else {
                            cout << "Connection error." << endl;
                        }

                    }
                }

                // button Exit
                if (ImGui::TableSetColumnIndex(1)) {
                    if (ImGui::Button("Exit", ButtonSize)) {
                        // on exit game?
                        Exit();
                    }
                }
            }
        }
        ImGui::EndTable();
    }
}

CString WndLogin::title()
{
    return ID_LOGIN_AREA;
}

WndLogin::WndLogin(NetworkService& network, GameScene* scene, String name, UShort width, UShort height, Boolean isShown)
	: network(network), WndBasic(scene, name, width, height, isShown)
{
}

WndLogin::~WndLogin()
{
}

void WndLogin::open(void(*Exit)())
{
    if (!isShown) {
        return;
    }

    if (!isThemePlaying()) {
        playTheme();
    }

    using namespace ImGui;

    if (ImGui::Begin(name.c_str(), NON_CLOSEABLE, wndflag::Unresize
        | wndflag::Unscroll
        | wndflag::Untitle
        | wndflag::Unmove)) {

            ////////////////////////// LOGIN AREA
            {
                // set new UI area window size
                ImGui::SetWindowSize(ImVec2(width, height));
                sf::Vector2u sceneSize = scene->getSize();
                float wndX = static_cast<float>(sceneSize.x);
                float wndY = static_cast<float>(sceneSize.y);
                float centerX = (wndX / 2) - (width / 2);
                float centerY = (wndY / 2) - (height / 2);
                ImGui::SetWindowPos(ImVec2(centerX, centerY));

                ////////////////////////// INPUT TABLE
                createInputArea();

                ////////////////////////// UTILS
                ImGui::Spacing();

                ////////////////////////// BUTTONS TABLE
                createButtonArea(Exit);
            }
            ImGui::End();
    }
}
