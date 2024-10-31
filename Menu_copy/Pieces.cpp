#include "Pieces.h"
#include "Textures.h"

using namespace sf;

TXT txt;

Piece::Piece(bool side)
{
    this->side = side;
    selectBox.setSize(Vector2f(pieceSize, pieceSize));
}

void Piece::draw(RenderWindow &window)
{
    sprite.setTexture(texture);
    sprite.setScale(pieceSize / sprite.getLocalBounds().width, pieceSize / sprite.getLocalBounds().height);
    window.draw(sprite);
}

Pawn::Pawn(bool side): Piece(side)
{
    type = PAWN;
    texture = txt.pieceTexture[side == 0 ? 0 : 6];
}

Knight::Knight(bool side): Piece(side)
{
    type = KNIGHT;
    texture = txt.pieceTexture[side == 0 ? 1 : 7];
}

Bishop::Bishop(bool side): Piece(side)
{
    type = BISHOP;
    texture = txt.pieceTexture[side == 0 ? 2 : 8];
}

Rook::Rook(bool side): Piece(side)
{
    type = ROOK;
    texture = txt.pieceTexture[side == 0 ? 3 : 9];
}

Queen::Queen(bool side): Piece(side)
{
    type = QUEEN;
    texture = txt.pieceTexture[side == 0 ? 4 : 10];
}

King::King(bool side): Piece(side)
{
    type = KING;
    texture = txt.pieceTexture[side == 0 ? 5 : 11];
}

bool Pawn::isValidMove(int sx, int sy, int ex, int ey, std::vector<std::vector<std::shared_ptr<Piece> > > &grid) 
{
    if (ex < 0 || ey < 0 || ex > 7 || ey > 7 || (grid[ex][ey] && grid[ex][ey]->side == side)) return false;
    
    // CROSS CAPTURE
    if (abs(sx - ex) == 1 && abs(ey - sy) == 1)
    {   
        int d = (side == BLACK ? 1 : -1);
        if (grid[ex][ey]) return ey - sy == d;
        return false;
    }

    //NORMAL MOVE
    if (side == BLACK)
    {
        int d = (sy == 1 ? 2 : 1);
        if (grid[ex][ey] || grid[sx][sy + 1]) return false ;
        return sx == ex && sy < ey && ey <= sy + d;
    } 
    else
    {
        int d = (sy == 6 ? -2 : -1) ;
        if (grid[ex][ey] || grid[sx][sy - 1]) return false ;
        return sx == ex && sy + d <= ey && ey < sy;
    }
    return false;
}

bool Knight::isValidMove(int sx, int sy, int ex, int ey, std::vector<std::vector<std::shared_ptr<Piece> > > &grid)
{
    if (ex < 0 || ey < 0 || ex > 7 || ey > 7 || (grid[ex][ey] && grid[ex][ey]->side == side)) return false;
    for (std::pair<int, int> d: dir) if (sx - ex == d.first && sy - ey == d.second) return true;
    return false;
}

bool Bishop::isValidMove(int sx, int sy, int ex, int ey, std::vector<std::vector<std::shared_ptr<Piece> > > &grid)
{
    if (ex < 0 || ey < 0 || ex > 7 || ey > 7 || (grid[ex][ey] && grid[ex][ey]->side == side)) return false;
    if (abs(sx - ex) != abs(sy - ey)) return false;

    int dx = (ex > sx ? 1 : -1),
        dy = (ey > sy ? 1 : -1);
    sx += dx;
    sy += dy;

    while (sx != ex || sy != ey)
    {
        if (grid[sx][sy]) return false ;
        sx += dx;
        sy += dy;
    }
    return true ;
}

bool Rook::isValidMove(int sx, int sy, int ex, int ey, std::vector<std::vector<std::shared_ptr<Piece> > > &grid)
{
    if (ex < 0 || ey < 0 || ex > 7 || ey > 7 || (grid[ex][ey] && grid[ex][ey]->side == side)) return false;
    if (sx != ex && sy != ey) return false;

    int dx = 0, dy = 0;
    if (sy != ey) dy = (ey > sy ? 1 : -1);
    else dx = (ex > sx ? 1 : - 1);
    sx += dx ;
    sy += dy ;

    while (sx != ex || sy != ey)
    {
        if (grid[sx][sy]) return false;
        sx += dx ;
        sy += dy ;
    }
    return true ;
}

bool Queen::isValidMove(int sx, int sy, int ex, int ey, std::vector<std::vector<std::shared_ptr<Piece> > > &grid)
{
    if (ex < 0 || ey < 0 || ex > 7 || ey > 7 || (grid[ex][ey] && grid[ex][ey]->side == side)) return false;
    if (abs(sx - ex) == abs(sy - ey) || sx == ex || sy == ey)
    {
        int dx = 0, dy = 0;
        if (sx != ex) dx = (ex > sx ? 1 : -1);
        if (sy != ey) dy = (ey > sy ? 1 : -1);
        sx += dx ;
        sy += dy;

        while (sx != ex || sy != ey)
        {
            if (grid[sx][sy]) return false ;
            sx += dx;
            sy += dy;
        }
        return true;
    } 
    return false ;
}

bool King::isValidMove(int sx, int sy, int ex, int ey, std::vector<std::vector<std::shared_ptr<Piece> > > &grid)
{
    if (ex < 0 || ey < 0 || ex > 7 || ey > 7 || (grid[ex][ey] && grid[ex][ey]->side == side)) return false;
    for (std::pair<int, int> d : dir) if (sx - ex == d.first && sy - ey == d.second) return true;
    return false;
}

Piece::~Piece() {};
Pawn::~Pawn() {};
Knight::~Knight() {};
Bishop::~Bishop() {};
Rook::~Rook() {};
Queen::~Queen() {};
King::~King() {};