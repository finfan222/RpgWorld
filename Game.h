// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

// TODO: override TcpSocket send, network(socket) to class, receive, utf_8

#include "System.h"
#include "NetworkService.h"
#include "WndLogin.h"
#include "WndInventory.h"
#include "ResourceManager.h"

using namespace std;

/////////////////////// Prototypes
void Exit();

/////////////////////// Static Vars
static NetworkService NetService;
static Boolean isLoggedIn;

static unique_ptr<sf::Clock> MainSceneDelta = make_unique<sf::Clock>();

/////////////////////// SCENES
static unique_ptr<GameScene> MainScene = make_unique<GameScene>(sf::VideoMode(conf::WINDOW_RESOLUTION[0], conf::WINDOW_RESOLUTION[1]), GAME_NAME);
static unique_ptr<WndLogin> LoginWindow = make_unique<WndLogin>(NetService, MainScene.get(), ID_LOGIN_AREA, 192, 96);
static unique_ptr<WndInventory> InventoryWindow = make_unique<WndInventory>(MainScene.get(), 12);

void f(bool* p_open) {
    ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Example: Long text display", p_open))
    {
        ImGui::End();
        return;
    }

    static int test_type = 0;
    static ImGuiTextBuffer log;
    static int lines = 0;
    ImGui::Text("Printing unusually long amount of text.");
    ImGui::Combo("Test type", &test_type,
        "Single call to TextUnformatted()\0"
        "Multiple calls to Text(), clipped\0"
        "Multiple calls to Text(), not clipped (slow)\0");
    ImGui::Text("Buffer contents: %d lines, %d bytes", lines, log.size());
    if (ImGui::Button("Clear")) { log.clear(); lines = 0; }
    ImGui::SameLine();
    if (ImGui::Button("Add 1000 lines"))
    {
        for (int i = 0; i < 1000; i++)
            log.appendf("%i The quick brown fox jumps over the lazy dog\n", lines + i);
        lines += 1000;
    }
    ImGui::BeginChild("Log");
    switch (test_type)
    {
    case 0:
        // Single call to TextUnformatted() with a big buffer
        ImGui::TextUnformatted(log.begin(), log.end());
        break;
    case 1:
    {
        // Multiple calls to Text(), manually coarsely clipped - demonstrate how to use the ImGuiListClipper helper.
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        ImGuiListClipper clipper;
        clipper.Begin(lines);
        while (clipper.Step())
            for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
                ImGui::Text("%i The quick brown fox jumps over the lazy dog", i);
        ImGui::PopStyleVar();
        break;
    }
    case 2:
        // Multiple calls to Text(), not clipped (slow)
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        for (int i = 0; i < lines; i++)
            ImGui::Text("%i The quick brown fox jumps over the lazy dog", i);
        ImGui::PopStyleVar();
        break;
    }
    ImGui::EndChild();
    ImGui::End();
}

/////////////////////// Main Loop
int main()
{
    ImGui::SFML::Init(*MainScene);
    static bool show_app_long_text = false;
    Item i1(0, 1, "NewItem1");
    Item i2(1, 2, "NewItem2");
    Item i3(2, 3, "NewItem3");
    Item i4(3, 4, "NewItem4");
    Item i5(4, 5, "NewItem5");
    Item i6(5, 6, "NewItem6");
    Item i7(6, 7, "NewItem7");
    Item i8(7, 8, "NewItem8");

    InventoryWindow->add(i1);
    InventoryWindow->add(i2);
    InventoryWindow->add(i3);
    InventoryWindow->add(i4);
    InventoryWindow->add(i5);
    InventoryWindow->add(i6);
    InventoryWindow->add(i7);
    InventoryWindow->add(i8);

    RESOURCE_MANAGER_API.loadImages(MainScene.get());
    RESOURCE_MANAGER_API.loadMusic();

    LoginWindow->init();
    
    while (MainScene->isOpen())
    {
        sf::Event event;
        while (MainScene->pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::V) {
                    cout << InventoryWindow->shown() << endl;
                    if (InventoryWindow->shown()) {
                        InventoryWindow->close();
                        cout << "closed" << endl;
                    }
                    else {
                        InventoryWindow->open(nullptr);
                    }
                }
            }

            if (event.type == sf::Event::Closed) {
                MainScene->close();
            }
        }
        ImGui::SFML::Update(*MainScene, MainSceneDelta->restart());

        // основной исполняемый код для отображения (логика включена)
        {
            ImGui::ShowDemoWindow(&isLoggedIn);
            LoginWindow->open(&Exit);
            if (InventoryWindow->shown()) {
                InventoryWindow->open(nullptr);
            }
        }

        MainScene->clear();
        LoginWindow->redraw();
        ImGui::SFML::Render(*MainScene);
        MainScene->display();
    }
    Exit();
    return EXIT_SUCCESS;
}

void Exit() {
    try {
        NetService.tryDisconnect();
        ImGui::SFML::Shutdown();
        MainScene->close();
        MainScene.release();
        exit(0);
    }
    catch (exception e) {
        exit(1);
    }
}