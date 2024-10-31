#include "Board.h"

using namespace sf;

Board::Board()
{
    boardTexture.loadFromFile("chess.com Assets/board.png");
    board.setTexture(boardTexture);
    board.setScale(boardSize / board.getLocalBounds().width, boardSize / board.getLocalBounds().height);

    grid.resize(8,std::vector<std::shared_ptr<Piece> >(8, nullptr));

    //PAWN
    grid[0][1] = std::make_shared<Pawn>(BLACK);
    grid[1][1] = std::make_shared<Pawn>(BLACK);
    grid[2][1] = std::make_shared<Pawn>(BLACK);
    grid[3][1] = std::make_shared<Pawn>(BLACK);
    grid[4][1] = std::make_shared<Pawn>(BLACK);
    grid[5][1] = std::make_shared<Pawn>(BLACK);
    grid[6][1] = std::make_shared<Pawn>(BLACK);
    grid[7][1] = std::make_shared<Pawn>(BLACK);
    grid[0][6] = std::make_shared<Pawn>(WHITE);
    grid[1][6] = std::make_shared<Pawn>(WHITE);
    grid[2][6] = std::make_shared<Pawn>(WHITE);
    grid[3][6] = std::make_shared<Pawn>(WHITE);
    grid[4][6] = std::make_shared<Pawn>(WHITE);
    grid[5][6] = std::make_shared<Pawn>(WHITE);
    grid[6][6] = std::make_shared<Pawn>(WHITE);
    grid[7][6] = std::make_shared<Pawn>(WHITE);

    //KNIGHT
    grid[6][0] = std::make_shared<Knight>(BLACK);
    grid[1][0] = std::make_shared<Knight>(BLACK);
    grid[1][7] = std::make_shared<Knight>(WHITE);
    grid[6][7] = std::make_shared<Knight>(WHITE);

    //BISHOP
    grid[2][0] = std::make_shared<Bishop>(BLACK);
    grid[5][0] = std::make_shared<Bishop>(BLACK);
    grid[2][7] = std::make_shared<Bishop>(WHITE);
    grid[5][7] = std::make_shared<Bishop>(WHITE);

    //ROOK
    grid[0][0] = std::make_shared<Rook>(BLACK);
    grid[7][0] = std::make_shared<Rook>(BLACK);
    grid[0][7] = std::make_shared<Rook>(WHITE);
    grid[7][7] = std::make_shared<Rook>(WHITE);

    //QUEEN
    grid[3][0] = std::make_shared<Queen>(BLACK);
    grid[3][7] = std::make_shared<Queen>(WHITE);

    //KING
    grid[4][0] = std::make_shared<King>(BLACK);
    grid[4][7] = std::make_shared<King>(WHITE);
}

bool Board::isInCheck(int kingX, int kingY, bool side)
{
    for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) if (grid[i][j] && grid[i][j]->side != side && grid[i][j]->isValidMove(i, j, kingX, kingY, grid)) return true;
    return false;
}

bool Board::checkDetect(int sx, int sy, int ex, int ey)
{
    bool side = grid[sx][sy]->side;
    std::shared_ptr<Piece> tmp = grid[ex][ey] ;
    grid[ex][ey] = grid[sx][sy] ;
    grid[sx][sy] = nullptr;

    int kingX = 0, kingY = 0;
    for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) if (grid[i][j] && grid[i][j]->type == KING && grid[i][j]->side == side)
    {
        kingX = i;
        kingY = j;
        break;
    }

    bool flag = isInCheck(kingX, kingY, side);
    grid[sx][sy] = grid[ex][ey] ;
    grid[ex][ey] = tmp;
    return !flag;
}

void Board::castle(int sx, int sy, int ex, int ey)
{
    int rx = (ex > sx ? 7 : 0),
        ry = sy,
        dx = (ex > sx ? 1 : -1);
    if (grid[rx][ry] && grid[rx][ry]->type == ROOK && grid[rx][ry]->isValidMove(rx, ry, sx + dx, sy, grid))
    {
        grid[sx + dx][sy] = grid[rx][ry];
        grid[ex][ey] = grid[sx][sy];
        grid[rx][ry] = nullptr;
        grid[sx][sy] = nullptr;
    } 
}

void Board::promote(int sx, int sy, int ex, int ey)
{
    grid[ex][ey] = std::make_shared<Queen>(grid[sx][sy]->side);
    grid[sx][sy] = nullptr;
}

void Board::enPassant(int sx, int sy, int ex, int ey)
{
    grid[ex][ey] = grid[sx][sy];
    grid[sx][sy] = nullptr;
    grid[ex][sy] = nullptr;
}

void Board::normalMove(int sx, int sy, int ex, int ey)
{
    grid[ex][ey] = grid[sx][sy];
    grid[sx][sy] = nullptr;
}

void Board::resetEnPassant(int sx, int sy, int ex, int ey)
{
    for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++)
        if (grid[i][j]) grid[i][j]->enPassant = 0;

    if (grid[ex][ey] && grid[ex][ey]->type == PAWN && abs(ey - sy) == 2) grid[ex][ey]->enPassant = 1;
}

bool Board::isCastle(int sx, int sy, int ex, int ey)
{
    if (grid[sx][sy]->type == KING && sy == ey && abs(sx - ex) == 2)
    {
        int rx = (ex > sx ? 7 : 0),
            ry = sy,
            dx = (ex > sx ? 1 : -1);
        if (grid[rx][ry] && grid[rx][ry]->type == ROOK && grid[rx][ry]->isValidMove(rx, ry, sx + dx, sy, grid))
            return !grid[sx][sy]->hasMoved && !grid[rx][ry]->hasMoved;
    }
    return false;
}

bool Board::isPromote(int sx, int sy, int ex, int ey)
{
    if (grid[sx][sy]->type != PAWN) return false;
    if (grid[sx][sy]->isValidMove(sx, sy, ex, ey, grid))
    {
        if (grid[sx][sy]->side == WHITE && ey == 0) return true;
        if (grid[sx][sy]->side == BLACK && ey == 7) return true;
    }
    return false;
}

bool Board::isEnPassant(int sx, int sy, int ex, int ey)
{
    if (grid[sx][sy]->type != PAWN) return false;
    int d = (grid[sx][sy]->side == BLACK ? 1 : -1);
    if (ey - sy == d && grid[ex][sy] && grid[ex][sy]->type == PAWN && grid[ex][sy]->side != grid[sx][sy]->side && grid[ex][sy]->enPassant) return true;
    return false;
}

bool Board::lastCheck(int sx, int sy, int ex, int ey)
{
    if (grid[sx][sy] && checkDetect(sx, sy, ex, ey))
    {
        if (isCastle(sx, sy, ex, ey)) return true;
        // if (isPromote(sx, sy, ex, ey)) return true;
        // if (isEnPassant(sx, sy, ex, ey)) return true;
        if (grid[sx][sy]->isValidMove(sx, sy, ex, ey, grid)) return true;
    }   
    return false;   
}

bool Board::makeMove(int sx, int sy, int ex, int ey)
{
    if (lastCheck(sx, sy, ex, ey))
    {

        makeHistory(sx, sy, ex, ey, grid[ex][ey]);

        if (isCastle(sx, sy, ex, ey)) 
        {
            if (grid[sx][sy]->type == KING) grid[sx][sy]->hasMoved = 1;
            if (grid[sx][sy]->type == ROOK) grid[sx][sy]->hasMoved = 1;
            std::cerr << "HELLo \n";
            castleSound.play();
            castle(sx, sy, ex, ey);
        }
        else 
        {
            if (grid[sx][sy]->type == KING) grid[sx][sy]->hasMoved = 1;
            if (grid[sx][sy]->type == ROOK) grid[sx][sy]->hasMoved = 1;
            
            if (isPromote(sx, sy, ex, ey))
            {
                promote(sx, sy, ex, ey);
            }
            else if (isEnPassant(sx, sy, ex, ey))
            {
                enPassant(sx, sy, ex, ey);
            }
            else 
            {
                std::cerr << "NOO \n";
                normalMove(sx, sy, ex, ey);
            }
        }


        resetEnPassant(sx, sy, ex, ey);

        return true;
    }
    return false;
}

void Board::drawBoard(RenderWindow &window)
{
    window.draw(board);
    for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) if (grid[i][j]) 
    {
        if (grid[i][j]->type == KING && isInCheck(i, j, grid[i][j]->side)) 
        {
            // checkSound.play();
            grid[i][j]->box.setPosition(pieceSize * i, pieceSize * j);
        }
        else grid[i][j]->box.setPosition(-pieceSize, -pieceSize);


        grid[i][j]->sprite.setPosition(pieceSize * i, pieceSize * j);
        grid[i][j]->draw(window);
    }
}

void Board::makeHistory(int sx, int sy, int ex, int ey, std::shared_ptr<Piece> &piece)
{
    // Clear undo history
    while (!unHistory.empty()) unHistory.pop();

    // Create new history
    int moveValue = sx + sy * 10 + ex * 100 + ey * 1000 + grid[sx][sy]->hasMoved * 10000;
    history.push(std::make_pair(moveValue, piece));
}  

bool Board::undo()
{
    if (history.empty()) return false;
    std::pair <int, std::shared_ptr<Piece> > curUndo = history.top();
    history.pop();
    unHistory.push(curUndo);

    int sx = (curUndo.first) % 10,
        sy = (curUndo.first / 10) % 10,
        ex = (curUndo.first / 100) % 10,
        ey = (curUndo.first / 1000) % 10,
        CastleState = (curUndo.first / 10000) % 10;

    grid[sx][sy] = grid[ex][ey];
    grid[ex][ey] = curUndo.second;

    if (grid[sx][sy] && grid[sx][sy]->type == KING && abs(sx - ex) == 2)
    {
    int rx = (ex > sx ? 7 : 0),
        ry = sy,
        dx = (ex > sx ? 1 : -1);
        
        grid[rx][ry] = grid[sx + dx][sy];
        grid[sx + dx][sy] = nullptr;
        grid[sx][sy]->hasMoved = 0;
        grid[rx][ry]->hasMoved = 0;
    }

    if(grid[sx][sy] && grid[sx][sy]->type == PAWN && abs(sy- sy) == 1 && grid[ex][ey] == nullptr)
    {
        grid[ex][sy] = std::make_shared<Pawn>(1-grid[sx][sy]->side) ; 
        grid[ex][sy]->enPassant = true ;
    }

    if (grid[sx][sy] && grid[sx][sy]->type == KING) grid[sx][sy]->hasMoved = CastleState;
    if (grid[sx][sy] && grid[sx][sy]->type == ROOK) grid[sx][sy]->hasMoved = CastleState;
    

    return true;
}

bool Board::redo()
{
    if (unHistory.empty()) return false; 
    std::pair<int , std::shared_ptr<Piece>> curRedo = unHistory.top();
    unHistory.pop();
    history.push(curRedo);
    int sx = (curRedo.first)  % 10,
        sy = (curRedo.first / 10) % 10 ,
        ex = (curRedo.first / 100) % 10 ,
        ey = (curRedo.first / 1000) % 10 ;

    grid[ex][ey] = grid[sx][sy] ; 
    grid[sx][sy] = nullptr;
        if(grid[ex][ey]->type == KING && abs(sx-ex) == 2)
    {
        
        // Find original position of rook and castle direction 
        int rx = (ex - sx) > 0 ? 7:0,   
            ry = sy ,
            dx = (ex - sx) > 0 ? 1:-1;
        grid[ex][ey]->hasMoved = 1 ; 
        grid[rx][ry]->hasMoved = 1 ; 
        grid[sx + dx][sy] = grid[rx][ry];
        grid[rx][ry] = nullptr;
        
    }

    if(grid[sx][sy] && grid[sx][sy]->type == PAWN && abs(sy- sy) == 1 && curRedo.second == nullptr)
    {
        grid[ex][sy] = nullptr;
    }    

    return true ;

}

Board::~Board() {};