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
    Texture pieceTexture[12];
    TXT()
    {
        pieceTexture[5].loadFromFile("Assets/chess.com/wk.png");
        pieceTexture[4].loadFromFile("Assets/chess.com/wq.png");
        pieceTexture[3].loadFromFile("Assets/chess.com/wr.png");
        pieceTexture[2].loadFromFile("Assets/chess.com/wb.png");
        pieceTexture[1].loadFromFile("Assets/chess.com/wn.png");
        pieceTexture[0].loadFromFile("Assets/chess.com/wp.png");
        pieceTexture[11].loadFromFile("Assets/chess.com/bk.png");
        pieceTexture[10].loadFromFile("Assets/chess.com/bq.png");
        pieceTexture[9].loadFromFile("Assets/chess.com/br.png");
        pieceTexture[8].loadFromFile("Assets/chess.com/bb.png");
        pieceTexture[7].loadFromFile("Assets/chess.com/bn.png");
        pieceTexture[6].loadFromFile("Assets/chess.com/bp.png");
    }
};