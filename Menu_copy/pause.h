#pragma once
#include "state.h"

class Pause : public State 
{
private:
    std::vector<std::shared_ptr<Button>> items;
public:
    Pause();

    void handleInput(sf::RenderWindow& window, sf::Event event) override;
    void update(sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;
};