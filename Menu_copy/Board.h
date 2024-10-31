#pragma once
#include "Pieces.h"
#include "state.h"
#include <stack>

class Board
{
private:
    bool clickCount = 0;

    int newX, newY, oldX, oldY;

    sf::Vector2i kingPos[2];

    sf::Cursor arrowCursor, handCursor;
    RectangleShape oldCell, newCell, alertBox;
    std::vector<CircleShape> validMoves;
    std::vector<std::vector<int>> moves;

public:
    bool turn = 0 ;
    Texture boardTexture, boardTexture2;
    Sprite board;

    SoundBuffer moveBuffer, captureBuffer, castleBuffer, checkBuffer, checkmateBuffer;
    Sound moveSound, captureSound, castleSound, checkSound, checkmateSound;
    
    std::stack<std::pair<int, std::shared_ptr<Piece> > > unHistory, history;
    std::vector<std::vector<std::shared_ptr<Piece> > > grid;

    Board();
    ~Board();

    void init();
    void resetGame();
    void handleInput(sf::RenderWindow& window, sf::Event event);
    void update(sf::RenderWindow& window);
    void drawBoard(RenderWindow& window, style curStyle);

    bool isInCheck(int kingX, int kingY);
    bool checkDetect(int sx, int sy, int ex, int ey);

    bool isCastle(int sx, int sy, int ex, int ey);
    bool isPromote(int sx, int sy, int ex, int ey);
    bool isEnPassant(int sx, int sy, int ex, int ey);
    bool lastCheck(int sx, int sy, int ex, int ey);

    void castle(int sx, int sy, int ex, int ey);
    void promote(int sx, int sy, int ex, int ey);
    void enPassant(int sx, int sy, int ex, int ey);
    void normalMove(int sx, int sy, int ex, int ey);
    bool makeMove(int sx, int sy, int ex, int ey);

    void resetEnPassant(int sx, int sy, int e, int ey);

    void makeHistory(int sx, int sy, int ex, int ey, std::shared_ptr<Piece> &piece);
    void undo();
    void redo();
};