
#include "GameMenu.h"
#include "MainCharacter.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "MapGrass.h"
#include "Enemy.h"
#include "ControlPanel.h"
#include "GameSaver.h"
#include "FrogMan.h"
#include <chrono>

using namespace sf;

auto window= sf::RenderWindow(
        VideoMode::getDesktopMode(), "Game",
        Style::Fullscreen, ContextSettings(0, 0, 8));

sf::View view=window.getDefaultView();
GameSaver save;
void InitText(Text& mtext, float xpos, float ypos, String str, int size_font=60, Color menu_text_color=Color::White);
void mainMenu();
void TheEnd(float mainCharacterPosX, float mainCharacterPosY);
void Card(MainCharacter& mainCharacter, std::vector<Enemy>& enemies, float mainCharacterPosX, float mainCharacterPosY, int phase) {
    float width = 900.0f;
    float height = 600.0f;
    RectangleShape background(Vector2f(width * 2.3f, height * 2));
    background.setPosition(mainCharacterPosX - width / 2 - 600, mainCharacterPosY - height / 2 - 300);


    Font font;
    if (!font.loadFromFile("fonts/Adventurer.ttf")) return;



    Text questionText("Select a card, just press 1 or 2 on your keyboard", font, 50);
    questionText.setFillColor(Color(211, 211, 211));
    questionText.setPosition(mainCharacterPosX - 520, mainCharacterPosY - 450);
    Texture texture_window;
    if(phase==2) {
        if (!texture_window.loadFromFile("images/card1.png")) return;
        background.setTexture(&texture_window);
    }
    if(phase==3) {
        if (!texture_window.loadFromFile("images/card2.png")) return;
        background.setTexture(&texture_window);
    }


    bool optionSelected = false;

    while (window.isOpen() && !optionSelected) {
        auto event = sf::Event();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            } else if (event.type == sf::Event::KeyPressed){
                if (event.key.code == Keyboard::Num1) {
                    for (auto &enemy: enemies) {
                        enemy.currentHP *= 3.0f;
                    }
                        mainCharacter.DMG();
                        optionSelected = true;
                } else if (event.key.code == Keyboard::Num2) {
                    for (auto &enemy: enemies) {
                        enemy.damage *= 2.0f;
                    }
                        mainCharacter.currentHP=7000;
                        optionSelected = true;
                }
            }


        }

        window.clear();
        window.draw(background);
        window.draw(questionText);
        window.display();
    }
}

void SaveGame(sf::RenderWindow& window, float mainCharacterPosX, float mainCharacterPosY, int phase) {
    float x = mainCharacterPosX;
    float y = mainCharacterPosY;

    view.setCenter(window.getDefaultView().getCenter());
    window.setView(view);

    float width = VideoMode::getDesktopMode().width;
    float height = VideoMode::getDesktopMode().height;

    RectangleShape background( Vector2f (width, height));


    Texture texture_window;
    if (!texture_window.loadFromFile("images/menu_background_SaveFile.png")) return;
    background.setTexture(&texture_window);


    Font font;
    if (!font.loadFromFile("fonts/Adventurer.ttf")) return;


    Text promptText("Enter the name of the save\n (use only Latin letters)", font, 60);
    promptText.setFillColor(sf::Color(8,6,2));
    promptText.setPosition(650, 300);

    Text inputText("", font, 50);
    inputText.setFillColor(sf::Color(61,46,21));
    inputText.setPosition(610, 680);

    std::string userInput;
    bool enterPressed = false;
    int inputIndex = 0;

    while (window.isOpen() && !enterPressed) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {

            } else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 13) {
                    enterPressed = true;
                } else if (event.text.unicode == 8 && !userInput.empty()) {
                    userInput.pop_back();
                    inputIndex--;
                    if (inputIndex < 0) inputIndex = 0;
                } else if (event.text.unicode < 128 && event.text.unicode != 8) {
                    userInput += static_cast<char>(event.text.unicode);
                    inputIndex++;
                }
            }
        }
        std::string displayedText = userInput.substr(0, inputIndex);

        inputText.setString(displayedText);

        window.clear();
        window.draw(background);
        window.draw(promptText);
        window.draw(inputText);
        window.display();
    }

    GameSaver save;
    std::vector<std::string> saveFiles = GameSaver::getSaveFiles();
    if (saveFiles.size() <= 3) {
        save.saveGame(userInput, x, y, phase);
    } else {
        std::cerr << "Maximum number of save files reached.";
    }


    mainMenu();
}


void Pause(float mainCharacterPosX, float mainCharacterPosY, int phase) {


    view.setCenter(window.getDefaultView().getCenter());
    window.setView(view);

    float width = VideoMode::getDesktopMode().width;
    float height = VideoMode::getDesktopMode().height;

    RectangleShape background( Vector2f (width, height));


    Texture texture_window;
    if (!texture_window.loadFromFile("images/pause.png")) return;
    background.setTexture(&texture_window);


    Font font;
    if (!font.loadFromFile("fonts/Adventurer.ttf")) return;

    Text NotquestionText("Pause", font, 80);
    NotquestionText.setFillColor(Color(211, 211, 211));
    NotquestionText.setPosition( 860, 100);

    Text questionText("Save the game if u want to leave?", font, 50);
    questionText.setFillColor(Color(211, 211, 211));
    questionText.setPosition( 100, 280);



        std::vector<String> name_menu {L"Leave without saving", L"Save and leave",L"Back to the game"};
        game::GameMenu mymenu(window, 230, 400, name_menu, 50, 180);
        mymenu.AlignMenu(2);

        while (window.isOpen()) {
            auto event = Event();
            while (window.pollEvent(event)) {
                if (event.type == Event::KeyReleased){
                    if (event.key.code == Keyboard::Up) { mymenu.MoveUp(); }
                    if (event.key.code == Keyboard::Down) { mymenu.MoveDown(); }
                    if (event.key.code == Keyboard::Space){

                        switch (mymenu.getSelectedMenuNumber())
                        {
                            case 0:mainMenu();   break;
                            case 1: SaveGame(window, mainCharacterPosX, mainCharacterPosY, phase);
                                mainMenu();
                                break;
                            case 2:return;
                        }
                    }
                }

            }
            window.clear();
            window.draw(background);
            window.draw(NotquestionText);
            window.draw(questionText);
            mymenu.draw();
            window.display();
        }

    }




void AfterDeath( float mainCharacterPosX, float mainCharacterPosY, int phase){
    view.setCenter(window.getDefaultView().getCenter());
    window.setView(view);

    float width = VideoMode::getDesktopMode().width;
    float height = VideoMode::getDesktopMode().height;

    RectangleShape background( Vector2f (width, height));

    Texture texture_window;
    if (!texture_window.loadFromFile("images/death.png")) return;
    background.setTexture(&texture_window);


    Font font;
    if (!font.loadFromFile("fonts/Adventurer.ttf")) return;
    Text  leaveText, continueText;
    InitText(continueText, 230, 400, "Save", 60, Color(211, 211, 211));
    continueText.setFont(font);
    InitText(leaveText, 230, 580, "Leave the game", 60, Color(211, 211, 211));
    leaveText.setFont(font);

    Text NotquestionText("You died", font, 90);
    NotquestionText.setFillColor(Color::Red);
    NotquestionText.setPosition(840, 30);

    Text questionText("Want to save the game or leave?", font, 60);
    questionText.setFillColor(Color(211, 211, 211));
    questionText.setPosition(mainCharacterPosX - 340, mainCharacterPosY - 200);



    bool isContinueSelected = true;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Up || event.key.code == Keyboard::Down) {
                    isContinueSelected = !isContinueSelected;
                }
                if (event.key.code == Keyboard::Space) {
                    if (isContinueSelected) {
                        mainMenu();
                    } else {
                        SaveGame(window, mainCharacterPosX, mainCharacterPosY, phase);
                        break;

                    }
                }
            }
        }


        continueText.setFillColor(isContinueSelected ?  Color(211, 211, 211):Color(178, 34, 34));
        leaveText.setFillColor(isContinueSelected ?  Color(178, 34, 34):Color(211, 211, 211));

        window.clear();
        window.draw(background);
        window.draw(continueText);
        window.draw(leaveText);
        window.draw(questionText);
        window.draw(NotquestionText);
        window.display();
    }

}



void GameStart(int heroX = -1, int heroY = -1, int phase = 1) {
    Font font;
    if (!font.loadFromFile("fonts/Adventurer.ttf")) return;
    Text pE;
    pE.setFont(font);
    pE.setFillColor(Color(211, 211, 211));
    pE.setCharacterSize(50);
    pE.setString("press E-key to teleport and end the mission");
    pE.setPosition(1800, 2700);

    Sprite portal;
    Texture mapDr;

    mapDr.loadFromFile("images/mapDragonPortal.png");
    portal.setTexture(mapDr);
    portal.setTextureRect(IntRect(0,0,461,386));
    portal.setPosition(1425,2165);
    portal.setScale(2.4,2.5);

    window.setMouseCursorVisible(false);
    MainCharacter mainCharacter;
    FrogMan frog;

    if (heroX != -1 && heroY != -1) {
        mainCharacter.setPosition(heroX, heroY);
    }
    MapGrass mapGrass;
    ControlPanel controlPanel(mainCharacter.getPosition());
    std::vector<Enemy> enemies = Enemy::createEnemies(phase);

    while (window.isOpen()) {
        Event event_play;
        while (window.pollEvent(event_play)) {
            if (event_play.type == Event::KeyPressed) {
                if (event_play.key.code == Keyboard::Escape) {
                    Pause(mainCharacter.getPositionX(), mainCharacter.getPositionY(), phase);
                    break;
                }
            }
        }
        window.clear(Color::Black);

        view.setCenter(mainCharacter.getPositionX(), mainCharacter.getPositionY());
        window.setView(view);
        mapGrass.draw(window);

        if (enemies.empty() && phase == 3){
            window.draw(portal);
            if(mainCharacter.getPositionY() >= 2700 && mainCharacter.getPositionY() < 3000 && mainCharacter.getPositionX() >= 700) {
                window.draw(pE);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                    TheEnd(mainCharacter.getPositionX(), mainCharacter.getPositionY());
                }
            }
        }
        mainCharacter.draw(window);
        mainCharacter.move();
        mainCharacter.lava(window);

        for (const auto& enemy : enemies) {
            enemy.draw(window);
        }
        for (auto& enemy : enemies) {
            enemy.update(enemies, mainCharacter.getPosition(), 400, mainCharacter.currentDmg);
            mainCharacter.HP(enemy.getPosition(), 100, enemy.damage, enemy.bss);
        }
        if (mainCharacter.isDead()){
                AfterDeath( mainCharacter.getPositionX(), mainCharacter.getPositionY(), phase);

        }
        enemies.erase(
                std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& enemy) { return enemy.currentHP <= 0; }),
                enemies.end()
        );

        if (enemies.empty() && Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            phase++;
            if (phase <= 3) {
                Card(mainCharacter,  enemies, mainCharacter.getPositionX(), mainCharacter.getPositionY(), phase);
                enemies = Enemy::createEnemies(phase);
            } else {
                phase = 3;
            }
        }
        frog.move();
        frog.draw(window, mainCharacter.getPosition());


        mainCharacter.scales(window);
        controlPanel.buttons_pict();
        controlPanel.Scull(phase);
        controlPanel.update(mainCharacter.getPosition(),phase);
        controlPanel.draw(window, phase);



        frog.Coins(phase, enemies, mainCharacter.getPosition(), mainCharacter);
        controlPanel.FrogShop(window,mainCharacter.getPosition());
        frog.draw2(window, mainCharacter.getPosition());
        for (const auto& obstacle : mapGrass.getObstacles()) {
            auto mainBounds = mainCharacter.getBottom();
            auto obstacleBounds = obstacle.getGlobalBounds();

            if (mainBounds.intersects(obstacleBounds)) {
                mainCharacter.moveBack();
                break;
            }
        }

        window.display();
    }
}
void ListOfSavings(){
    float width = VideoMode::getDesktopMode().width;
    float height = VideoMode::getDesktopMode().height;

    RectangleShape background( Vector2f (width, height));
    Texture texture_window;

    texture_window.loadFromFile("images/menu_background_AboutGame.png");
    background.setTexture(&texture_window);



    Font mfont;
    if (!mfont.loadFromFile("fonts/Adventurer.ttf")) {std::cout<<"file not found";};



    std::vector<std::string> saveFiles = save.getSaveFiles();
    if (saveFiles.empty()) {
        std::cout << "No saved games found";
        return;
    }
    std::vector<String> name_mysavings;
    for (const auto& file : saveFiles) {
        name_mysavings.push_back(file);
    }


    game::GameMenu mysavings(window, 720, 300, name_mysavings, 90, 120);
    mysavings.AlignMenu(2);

    while (window.isOpen()) {
        auto event = Event();
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Up) {
                    mysavings.MoveUp();
                }
                if (event.key.code == Keyboard::Down) {
                    mysavings.MoveDown();
                }
                if (event.key.code == Keyboard::Space) {
                    int selected = mysavings.getSelectedMenuNumber();
                    if (selected >= 0 && selected < saveFiles.size()) {
                        int heroX, heroY, phase;
                        if (save.loadGame(saveFiles[selected], heroX, heroY, phase)) {

                            GameStart(heroX, heroY, phase);
                        } else {
                            std::cout << "Failed to load game";
                        }
                    }
                }
                else if (event.key.code==Keyboard::Escape){
                    return;
                }
            }
        }
        window.clear();
        window.draw(background);
        mysavings.draw();
        window.display();
    }
}
void MainControl(){
    float width = VideoMode::getDesktopMode().width;
    float height = VideoMode::getDesktopMode().height;

    RectangleShape background( Vector2f (width, height));
    Texture texture_window;

    texture_window.loadFromFile("images/AboutGameMainControl.png");
    background.setTexture(&texture_window);


    while (window.isOpen()) {
        auto event = Event();
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyReleased) {
                if (event.key.code==Keyboard::Escape){
                    return;
                }
            }
        }
        window.clear();
        window.draw(background);

        window.display();
    }
}


void TheEnd(float mainCharacterPosX, float mainCharacterPosY){
    float width = 900.0f;
    float height = 600.0f;

    RectangleShape background(Vector2f(width*2.3f, height*2));
    background.setPosition(mainCharacterPosX - width / 2-600, mainCharacterPosY - height / 2-300);

    Texture texture_window;
    if (!texture_window.loadFromFile("images/theEnd.png")) return;
    background.setTexture(&texture_window);

    Font font;
    if (!font.loadFromFile("fonts/Adventurer.ttf")) return;
    Text  leaveText, continueText;

    Text EndText("The End.", font, 70);
    EndText.setFillColor(Color(211, 211, 211));
    EndText.setPosition(mainCharacterPosX - 110, mainCharacterPosY - 300);

    Text bText("press enter to leave the game", font, 50);
    bText.setFillColor(Color(211, 211, 211));
    bText.setPosition(mainCharacterPosX - 200, mainCharacterPosY + 250);

    bool isContinueSelected = true;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Enter ) {
                    mainMenu();
                }
            }
        }
        continueText.setFillColor(isContinueSelected ?  Color(211, 211, 211):Color(178, 34, 34));
        leaveText.setFillColor(isContinueSelected ?  Color(178, 34, 34):Color(211, 211, 211));

        window.clear();
        window.draw(background);
        window.draw(EndText);
        window.draw(bText);
        window.display();
    }
}
void mainMenu(){
    window.setMouseCursorVisible(false);

    view.setCenter(window.getDefaultView().getCenter());
    window.setView(view);

    float width=VideoMode::getDesktopMode().width;
    float height=VideoMode::getDesktopMode().height;

    RectangleShape background( Vector2f (width, height));
    Texture texture_window;

    texture_window.loadFromFile("images/menu_background.png");
    background.setTexture(&texture_window);



    Font mfont;
    mfont.loadFromFile("fonts/Adventurer.ttf") ;



    std::vector<String> name_menu {L"New Game", L"Savings",L"Main control", L"Exit"};
    game::GameMenu mymenu(window, 230, 400, name_menu, 90, 120);
    mymenu.AlignMenu(2);

    while (window.isOpen()) {
        auto event = Event();
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyReleased){
                if (event.key.code == Keyboard::Up) { mymenu.MoveUp(); }
                if (event.key.code == Keyboard::Down) { mymenu.MoveDown(); }
                if (event.key.code == Keyboard::Space){

                    switch (mymenu.getSelectedMenuNumber())
                    {
                        case 0:GameStart();   break;
                        case 1:ListOfSavings(); break;
                        case 2:MainControl(); break;
                        case 3:window.close(); break;

                    }
                }
            }

        }
        window.clear();
        window.draw(background);
        mymenu.draw();


        window.display();
    }

}

auto main() -> int{
    mainMenu();
}




void InitText (Text& mtext, float xpos, float ypos, String str, int size_font, Color menu_text_color) {
    mtext.setCharacterSize(size_font);
    mtext.setPosition(xpos, ypos);
    mtext.setString(str);
    mtext.setFillColor(menu_text_color);
}
