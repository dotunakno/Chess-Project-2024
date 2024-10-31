#include "menu.h"

Menu::Menu() 
{
    backgroundImg.loadFromFile("Assets/chess.com/menu-background.png");
    background.setSize(Vector2f(screenWidth, screenHeight));
    background.setTexture(&backgroundImg);

    items.resize(3, nullptr);
    items[0] = std::make_shared<Button>("Play", 0, 0);
    items[1] = std::make_shared<Button>("Settings", 0, 200);
    items[2] = std::make_shared<Button>("Exit", 0, 400);
}

void Menu::handleInput(sf::RenderWindow& window, sf::Event event) 
{
    for (auto item: items) item->handleEvent(window, event);
    if (items[0]->isClicked(window, event))
    {
        stateSwitch = 1;
        newState = GAME;
    }

    if (items[1]->isClicked(window, event))
    {
        stateSwitch = 1;
        newState = SETTINGS;
    }

    if (items[2]->isClicked(window, event)) 
    {
        window.close();
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
        stateSwitch = 1;
        newState = GAME;
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
        stateSwitch = 1;
        newState = SETTINGS;
    }
}

void Menu::update(sf::RenderWindow& window) {}

void Menu::render(sf::RenderWindow& window) 
{
    window.clear();
    window.draw(background);
    for (auto item: items) item->run(window);
    window.display();
}