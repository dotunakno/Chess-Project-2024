#pragma once
#include "button.h"
#include "state.h"

class Menu : public State 
{
private:
    std::vector<std::shared_ptr<Button>> items;
    sf::Texture backgroundImg;
    sf::RectangleShape background;
public:
    Menu();

    void handleInput(sf::RenderWindow& window, sf::Event event) override;
    void update(sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;
};