#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Textures.h"
#include "Variables.h"
#include "button.h"
#include <new>

enum state {MENU, GAME, PAUSE, SETTINGS};
enum style {MODERN, CLASSIC, CARTOON};

class State 
{
public:
    bool stateSwitch = 0;
    state newState;
    style curStyle = MODERN;

    virtual void handleInput(sf::RenderWindow& window, sf::Event event) = 0;
    virtual void update(sf::RenderWindow& window) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};
