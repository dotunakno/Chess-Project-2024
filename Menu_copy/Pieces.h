#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Cursor.hpp>
#include "Variables.h"
#include <memory>
using namespace sf;

enum Type {PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING};

#define Side    bool
#define WHITE   0
#define BLACK   1

class Piece
{
public:
    bool side;
    Texture texture;
    Sprite sprite;
    Type type;
    Color color;
    RectangleShape selectBox;

    bool isSelected = 0;
    bool hasMoved = 0;
    bool enPassant = 0;

    Piece(bool side);
    ~Piece();
    virtual bool isValidMove(int sx, int sy, int ex, int ey, std::vector<std::vector<std::shared_ptr<Piece> > > &grid) = 0;
    void draw(RenderWindow& window);

    // bool isHovered(RenderWindow& window)
    // {
    //     return sprite.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
    // }

    // void toggleCheck(RenderWindow& window, Event event)
    // {
    //     if(event.type == sf::Event::MouseButtonPressed && isHovered(window)) isSelected = 1;
    // }
};

class Pawn: public Piece 
{
public:
    Pawn(bool side);
    ~Pawn();
    bool isValidMove(int sx, int sy, int ex, int ey, std::vector<std::vector<std::shared_ptr<Piece> > > &grid) override;
};

class Knight: public Piece 
{
private:
    std::vector<std::pair<int, int> > dir = {{1, 2}, {1, -2}, {2, 1}, {2, -1}, {-1, 2}, {-1, -2}, {-2, 1}, {-2, -1}};

public:
    Knight(bool side);
    ~Knight();
    bool isValidMove(int sx, int sy, int ex, int ey, std::vector<std::vector<std::shared_ptr<Piece> > > &grid) override;
};

class Bishop: public Piece 
{
public:
    Bishop(bool side);
    ~Bishop();
    bool isValidMove(int sx, int sy, int ex, int ey, std::vector<std::vector<std::shared_ptr<Piece> > > &grid) override;
};

class Rook: public Piece 
{
public:

    Rook(bool side);
    ~Rook();
    bool isValidMove(int sx, int sy, int ex, int ey, std::vector<std::vector<std::shared_ptr<Piece> > > &grid) override;
};

class Queen: public Piece 
{
public:
    Queen(bool side);
    ~Queen();
    bool isValidMove(int sx, int sy, int ex, int ey, std::vector<std::vector<std::shared_ptr<Piece> > > &grid) override;
};

class King: public Piece 
{
private:
    std::vector<std::pair<int, int> > dir = {{1, 0}, {1, 1}, {1, -1}, {-1, 0}, {-1, 1}, {-1, -1}, {0, 1}, {0, -1}};

public:
    King(bool side);
    ~King();
    bool isValidMove(int sx, int sy, int ex, int ey, std::vector<std::vector<std::shared_ptr<Piece> > > &grid) override;
};