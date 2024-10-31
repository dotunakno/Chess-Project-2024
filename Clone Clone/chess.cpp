#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Cursor.hpp>
#include "Pieces.h"
#include "Board.h"

using namespace sf;

int main()
{
    // WINDOW:
    RenderWindow window(VideoMode(screenWidth, screenHeight), "Chess", Style::Close);
    window.setFramerateLimit(FPS);

    // CURSOR
    Cursor cursor;
    if (cursor.loadFromSystem(Cursor::Hand)) window.setMouseCursor(cursor);

    RectangleShape oldCell(Vector2f(pieceSize, pieceSize));
    RectangleShape newCell(Vector2f(pieceSize, pieceSize));
    oldCell.setFillColor(Color(0, 0, 0, 96));
    newCell.setFillColor(Color(255, 255, 255, 128));
    
    bool turn = 0, clickCount = 0;
    int newX, newY, oldX = -1, oldY = -1;

    std::vector<CircleShape> validMoves;
    std::vector<std::vector<int> > moves;

    Board mainBoard;
    while (window.isOpen())
    {
        moves.clear();
        for (int i1 = 0; i1 < 8; i1++) for (int j1 = 0; j1 < 8; j1++) for (int i2 = 0; i2 < 8; i2++) for (int j2 = 0; j2 < 8; j2++)
            if (mainBoard.lastCheck(i1, j1, i2, j2) && mainBoard.grid[i1][j1]->side == turn) moves.push_back({i1, j1, i2, j2});

        newX = Mouse::getPosition(window).x / pieceSize;
        newY = Mouse::getPosition(window).y / pieceSize;

        if (moves.size() == 0) 
        {
            window.close();
            std::cout << (turn ? "WHITE" : "BLACK") << " wins";
            return 0;
        }

        // // EASY MODE (RANDOM MOVE)
        // if (turn == 1) 
        // {
        //     if (moves.size() == 0) 
        //     {
        //         window.close();
        //         std::cout << (turn ? "WHITE" : "BLACK") << " wins";
        //         return 0;
        //     }
        //     else
        //     {
        //         int r = std::rand() % moves.size();
        //         std::cerr << moves[r][0] << " " << moves[r][1] << " " << moves[r][2] << " " << moves[r][3] << "\n";
        //         mainBoard.makeMove(moves[r][0], moves[r][1], moves[r][2], moves[r][3]);
        //         turn = 0;
        //     }
        // }

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) window.close();

            if (event.type == Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case (Keyboard::Q):
                        if (mainBoard.undo())
                        {
                            turn = !turn;
                            validMoves.clear();
                        }
                        break;
                    case (Keyboard::R):
                        if (mainBoard.redo())
                        {
                            turn = !turn;
                            validMoves.clear();
                        }
                        break;
                    default:
                        break;
                }
            }

            if (event.type == Event::MouseButtonPressed)
            {
                if (clickCount == 1)
                {  
                    if (mainBoard.makeMove(oldX, oldY, newX, newY)) turn = !turn;
                    oldX = -1;
                    oldY = -1;
                    clickCount = 0; 
                    validMoves.clear();
                }
                else 
                {
                    if (mainBoard.grid[newX][newY] && mainBoard.grid[newX][newY]->side == turn) 
                    {
                        oldX = newX;
                        oldY = newY;
                        clickCount = 1;

                        // SHOW VALID MOVES
                        for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) if (mainBoard.lastCheck(oldX, oldY, i, j))
                        {
                            CircleShape newMove(radius);
                            newMove.setPosition(pieceSize * (i + 0.5) - radius, pieceSize * (j + 0.5) - radius);
                            newMove.setFillColor(Color(255, 0, 0, 96));
                            if (mainBoard.grid[i][j]) newMove.setPointCount(4);
                            validMoves.push_back(newMove);
                        }
                    } 
                    else 
                    {
                        oldX = -1;
                        oldY = -1;
                        validMoves.clear();
                    }
                }
            }
        };

        oldCell.setPosition(pieceSize * oldX, pieceSize * oldY);
        newCell.setPosition(pieceSize * newX, pieceSize * newY);

        window.clear();
        mainBoard.drawBoard(window);
        for (auto move: validMoves) window.draw(move);
        window.draw(oldCell);
        window.draw(newCell);
        window.display();
    }

    return 0;
}