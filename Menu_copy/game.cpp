#include "game.h"
#include <new>

Game::Game()
{
    mainBoard.resetGame();
}

void Game::handleInput(sf::RenderWindow& window, sf::Event event) 
{
    // for (Button& button: buttons) button.handleEvent(window, event);

    if (undoButton.isClicked(window, event)) mainBoard.undo();
    if (redoButton.isClicked(window, event)) mainBoard.redo();
    if (resetButton.isClicked(window, event)) mainBoard.resetGame();

    mainBoard.handleInput(window, event);

    if (event.type == Event::KeyPressed)
    {
        switch(event.key.code)
        {   
            case (Keyboard::G):
                
                int sx,sy,ex,ey;
                std::tie(sx,sy,ex,ey) =stockfish.FindBest(mainBoard.history);
                mainBoard.makeMove(sx,sy,ex,ey);
                mainBoard.turn = mainBoard.turn^1; 
                break;
            case (Keyboard::Escape):
                stateSwitch = 1;
                newState = MENU;
                break;
            case (Keyboard::P):
                stateSwitch = 1;
                newState = PAUSE;
                break; 
            case (Keyboard::K):
                if (curStyle == MODERN) curStyle = CLASSIC;
                else curStyle = MODERN;
                break;
            default:
                break;
        }
    }
}

void Game::update(sf::RenderWindow& window)
{
    mainBoard.update(window);  
}

void Game::render(sf::RenderWindow& window) 
{
    window.clear();

    for (Button& button: buttons) button.run(window);

    // resetButton.run(window);

    mainBoard.drawBoard(window, curStyle);
    window.display();
}