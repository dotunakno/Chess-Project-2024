#include "pause.h"

Pause::Pause()
{

    items.resize(1, nullptr);
    items[0] = std::make_shared<Button>("Press P to resume", 0, 0);
}

void Pause::handleInput(sf::RenderWindow& window, sf::Event event) 
{
    // for (auto item: items) item->handleEvent(window, event);

    if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) || items[0]->isClicked(window, event)) {
        stateSwitch = 1;
        newState = GAME;
    }
}

void Pause::update(sf::RenderWindow& window) {};

void Pause::render(sf::RenderWindow& window) 
{
    window.clear();
    for (auto item: items) item->run(window);
    window.display();
}