#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Cursor.hpp>
#include "Variables.h"

// #define NULL            

using namespace sf;

class TXT
{
public:
    Texture empty, boardTexture, pieceTexture[12];
    TXT()
    {
        // boardTexture.loadFromFile("/Users/namkiet/Desktop/Chess/chess.com Assets/board.png");
        pieceTexture[5].loadFromFile("chess.com Assets/wk.png");
        pieceTexture[4].loadFromFile("chess.com Assets/wq.png");
        pieceTexture[3].loadFromFile("chess.com Assets/wr.png");
        pieceTexture[2].loadFromFile("chess.com Assets/wb.png");
        pieceTexture[1].loadFromFile("chess.com Assets/wn.png");
        pieceTexture[0].loadFromFile("chess.com Assets/wp.png");
        pieceTexture[11].loadFromFile("chess.com Assets/bk.png");
        pieceTexture[10].loadFromFile("chess.com Assets/bq.png");
        pieceTexture[9].loadFromFile("chess.com Assets/br.png");
        pieceTexture[8].loadFromFile("chess.com Assets/bb.png");
        pieceTexture[7].loadFromFile("chess.com Assets/bn.png");
        pieceTexture[6].loadFromFile("chess.com Assets/bp.png");
    }
};