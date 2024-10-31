#pragma once
#include "Pieces.h"
#include <stack>

class Board
{
private:
    Texture boardTexture;
    Sprite board;
public:
    SoundBuffer moveBuffer, captureBuffer, castleBuffer, checkBuffer, checkmateBuffer;
    Sound moveSound, captureSound, castleSound, checkSound, checkmateSound;
    
    std::stack<std::pair<int, std::shared_ptr<Piece> > > unHistory, history;
    std::vector<std::vector<std::shared_ptr<Piece> > > grid;

    Board();
    ~Board();

    bool isInCheck(int kingX, int kingY, bool side);
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

    void drawBoard(RenderWindow &window);

    void makeHistory(int sx, int sy, int ex, int ey, std::shared_ptr<Piece> &piece);
    bool undo();
    bool redo();
};