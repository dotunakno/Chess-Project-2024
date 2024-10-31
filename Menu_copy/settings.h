#pragma once
#include "state.h"

class Settings : public State 
{
private:
    std::vector<std::shared_ptr<Button>> items;
public:
    Settings();

    void handleInput(sf::RenderWindow& window, sf::Event event) override;
    void update(sf::RenderWindow& window) override {};
    void render(sf::RenderWindow& window) override;
};