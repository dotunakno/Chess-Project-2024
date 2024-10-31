#pragma once
#include "state.h"
#include "Board.h"
#include "AI.h"
class Game : public State 
{
private:
    Board mainBoard;
    // Button undoButton, redoButton, resetButton;
    Button undoButton       = Button("Undo", pieceSize * 8, 0, pieceSize, pieceSize, sf::Color::Red);
    Button redoButton       = Button("Redo", pieceSize * 9, 0, pieceSize, pieceSize, sf::Color::Green);
    Button resetButton      = Button("Reset", pieceSize * 8, pieceSize * 6, screenWidth - boardSize, pieceSize);
    Button settingsButton   = Button("Settings", pieceSize * 10, 0, screenWidth - boardSize - pieceSize * 2, pieceSize, sf::Color::Blue);
    StockFish stockfish;
    std::vector<Button> buttons = {undoButton, redoButton, resetButton, settingsButton};
public:
    
    Game();
    void handleInput(sf::RenderWindow& window, sf::Event event) override;
    void update(sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;
};