#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Variables.h"
#include <memory>

enum buttonState {IDLE, HOVERED, PRESSED};

class Button
{
public:
    sf::Font font;
    sf::Text text;
    sf::RectangleShape shape;
    sf::Color color;
    sf::Color idleColor     = sf::Color(255, 0, 0, 96);
    sf::Color hoveredColor  = sf::Color(0, 0, 255, 96);
    sf::Color pressedColor  = sf::Color(0, 255, 0, 96);
    buttonState state;

    Button(std::string content, float x, float y, float width = screenWidth, float height = pieceSize, sf::Color color = sf::Color::Transparent)
    {
        font.loadFromFile("Fonts/arial.ttf");
        state = IDLE;  
        
        idleColor = color;

        text.setFont(font);
        text.setString(content);
        text.setPosition(x, y);
        
        shape.setFillColor(color);
        shape.setPosition(x, y);
        shape.setSize(sf::Vector2f(width, height));
    }

    bool isClicked(sf::RenderWindow& window, sf::Event event)
    {
        return event.type == sf::Event::MouseButtonPressed && shape.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
    }

    void handleEvent(sf::RenderWindow& window, sf::Event event)
    {   
        if (isClicked(window, event))
        {
            if (state == PRESSED) state = IDLE;
            else state = PRESSED;
        }
    }

    void run(sf::RenderWindow& window)
    {   
        switch (state)
        {
            case IDLE:
                color = idleColor;
                break;
            case HOVERED:
                color = hoveredColor;
                break;
            case PRESSED:
                color = pressedColor;
                break;
            default:
                color = sf::Color::Black;
                break;
        }

        shape.setFillColor(color);
        window.draw(shape);
        window.draw(text);
    }    
};