#include "settings.h"

Settings::Settings() 
{

    items.resize(3, nullptr);
    items[0] = std::make_shared<Button>("MODERN", 0, 0);
    items[1] = std::make_shared<Button>("CLASSIC", 0, 200);
    items[2] = std::make_shared<Button>("Return", 0, 400);
}

void Settings::handleInput(sf::RenderWindow& window, sf::Event event) 
{
    items[0]->handleEvent(window, event);
    items[1]->handleEvent(window, event);

    if (items[0]->isClicked(window, event))
    {
        curStyle = CLASSIC;
        stateSwitch = 1;
        newState = GAME;
    }
    // else curStyle = MODERN;

    if (items[2]->isClicked(window, event) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
    {
        stateSwitch = 1;
        newState = MENU;
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
        stateSwitch = 1;
        newState = GAME;
    }
}

void Settings::render(sf::RenderWindow& window) 
{
    window.clear();
    for (auto item: items) item->run(window);
    window.display();
}