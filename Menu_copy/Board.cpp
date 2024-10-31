#include "Board.h"
#include "state.h"

using namespace sf;

Board::Board() {
    arrowCursor.loadFromSystem(Cursor::Arrow);
    handCursor.loadFromSystem(Cursor::Hand);
    oldCell.setSize(Vector2f(pieceSize, pieceSize));
    oldCell.setFillColor(Color(0, 0, 0, 96));
    newCell.setSize(Vector2f(pieceSize, pieceSize));
    newCell.setFillColor(Color(255, 255, 255, 128));
    alertBox.setSize(Vector2f(pieceSize, pieceSize));
    alertBox.setFillColor(Color(255, 0, 0, 64));

    boardTexture.loadFromFile("Assets/chess.com/board.png");
    boardTexture2.loadFromFile("Assets/classic/Board.png");

    moveBuffer.loadFromFile("Sound Effects/move.mp3");
    captureBuffer.loadFromFile("Sound Effects/capture.mp3");
    castleBuffer.loadFromFile("Sound Effects/castle.mp3");
    checkBuffer.loadFromFile("Sound Effects/check.mp3");
    moveSound.setBuffer(moveBuffer);
    captureSound.setBuffer(captureBuffer);
    castleSound.setBuffer(castleBuffer);
    checkSound.setBuffer(checkBuffer);
};

void Board::resetGame()
{
    turn = clickCount = 0;
    oldX = oldY = -1;

    // whiteKingX = 4;
    // whiteKingY = 7;
    // blackKingX = 4;
    // blackKingY = 0;
    kingPos[0] = sf::Vector2i(4, 7);
    kingPos[1] = sf::Vector2i(4, 0);

    while (!history.empty()) history.pop();
    while (!unHistory.empty()) unHistory.pop();

    grid.clear();
    grid.resize(8, std::vector<std::shared_ptr<Piece> >(8, nullptr));

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

void Board::handleInput(sf::RenderWindow& window, sf::Event event)
{
    if (event.type == Event::KeyPressed)
    {
        switch(event.key.code)
        {
            case (Keyboard::M):
                resetGame();
                break; 
            default:
                break;
        }
    }

    if (event.type == Event::MouseButtonPressed)
    {
        if (clickCount == 1)
        {
            clickCount = 0; 
            grid[oldX][oldY]->isSelected = 0;
            if (makeMove(oldX, oldY, newX, newY)) turn = !turn;
            oldX = -1;
            oldY = -1;
            validMoves.clear();
        }
        else 
        {
            if (newX != -1 && newY != -1 && grid[newX][newY] && grid[newX][newY]->side == turn) 
            {
                clickCount = 1;
                grid[newX][newY]->isSelected = 1;
                oldX = newX;
                oldY = newY;

                // SHOW VALID MOVES
                for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) if (lastCheck(oldX, oldY, i, j))
                {
                    CircleShape newMove(radius);
                    newMove.setPosition(pieceSize * (i + 0.5) - radius, pieceSize * (j + 0.5) - radius);
                    newMove.setFillColor(Color(255, 0, 0, 96));
                    if (grid[i][j]) newMove.setPointCount(4);
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


}

void Board::update(sf::RenderWindow& window)
{
    // std::cerr << oldX << "-" << oldY << " " << newX << " " << newY << "\n";

    moves.clear();
    for (int i1 = 0; i1 < 8; i1++) for (int j1 = 0; j1 < 8; j1++) for (int i2 = 0; i2 < 8; i2++) for (int j2 = 0; j2 < 8; j2++)
        if (lastCheck(i1, j1, i2, j2) && grid[i1][j1]->side == turn) moves.push_back({i1, j1, i2, j2});

    if (moves.size() == 0) 
    {
        window.close();
        std::cerr << (turn ? "WHITE" : "BLACK") << " wins";
        exit(0);
    }

    // // EASY MODE (RANDOM MOVE)
    // if (turn == 1)
    // {
    //     int r = std::rand() % moves.size();
    //     // std::cerr << moves[r][0] << " " << moves[r][1] << " " << moves[r][2] << " " << moves[r][3] << "\n";
    //     makeMove(moves[r][0], moves[r][1], moves[r][2], moves[r][3]);
    //     turn = 0;
    // }

    newX = Mouse::getPosition(window).x / pieceSize;
    newY = Mouse::getPosition(window).y / pieceSize;

    if (newX < 0 || newX > 7 || newY < 0 || newY > 7) 
    {
        newX = -1;
        newY = -1;
        window.setMouseCursor(arrowCursor);
    }
    else 
        window.setMouseCursor(handCursor);

    oldCell.setPosition(pieceSize * oldX, pieceSize * oldY);
    newCell.setPosition(pieceSize * newX, pieceSize * newY);    
    if (isInCheck(kingPos[turn].x, kingPos[turn].y))
        alertBox.setPosition(pieceSize * kingPos[turn].x, pieceSize * kingPos[turn].y);
    else 
        alertBox.setPosition(-pieceSize, -pieceSize);
}

void Board::drawBoard(RenderWindow &window, style curStyle)
{
    if (curStyle == MODERN) 
        board.setTexture(boardTexture, true);
    else 
        board.setTexture(boardTexture2, true);

    board.setScale(boardSize / board.getTexture()->getSize().x, boardSize / board.getTexture()->getSize().y);

    window.draw(board);
    window.draw(oldCell);
    window.draw(newCell);
    window.draw(alertBox);

    for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) if (grid[i][j])   
    {
        if (grid[i][j]->isSelected) 
            grid[i][j]->sprite.setPosition(Mouse::getPosition(window).x - pieceSize / 2, Mouse::getPosition(window).y - pieceSize / 2);
        else 
            grid[i][j]->sprite.setPosition(pieceSize * i, pieceSize * j);

        grid[i][j]->draw(window);
    }

    for (auto move: validMoves) window.draw(move);
}

bool Board::isInCheck(int kingX, int kingY)
{
    for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) if (grid[i][j] && grid[i][j]->isValidMove(i, j, kingX, kingY, grid)) return true;
    return false;
}

bool Board::checkDetect(int sx, int sy, int ex, int ey)
{
    bool side = grid[sx][sy]->side;
    std::shared_ptr<Piece> tmp = grid[ex][ey] ;
    if (grid[sx][sy]->type == KING) kingPos[side] = Vector2i(ex, ey);

    grid[ex][ey] = grid[sx][sy];
    grid[sx][sy] = nullptr;

    bool flag = isInCheck(kingPos[side].x, kingPos[side].y);
    grid[sx][sy] = grid[ex][ey] ;
    grid[ex][ey] = tmp;
    if (grid[sx][sy]->type == KING) kingPos[side] = Vector2i(sx, sy);
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
        if (isPromote(sx, sy, ex, ey)) return true;
        if (isEnPassant(sx, sy, ex, ey)) return true;
        if (grid[sx][sy]->isValidMove(sx, sy, ex, ey, grid)) return true;
    }   
    return false;   
}

bool Board::makeMove(int sx, int sy, int ex, int ey)
{
    if (lastCheck(sx, sy, ex, ey))
    {
        // grid[sx][sy]->isSelected = 0;
        if (grid[sx][sy]->type == KING)
        {
            kingPos[grid[sx][sy]->side] = Vector2i(ex, ey);
        }

        makeHistory(sx, sy, ex, ey, grid[ex][ey]);

        if (isCastle(sx, sy, ex, ey)) 
        {
            castleSound.play();
            castle(sx, sy, ex, ey);
        }
        else 
        {
            if (grid[sx][sy]->type == KING || grid[sx][sy]->type == ROOK) grid[sx][sy]->hasMoved = 1;
            
            
            if (isEnPassant(sx, sy, ex, ey))
            {
                captureSound.play();
                enPassant(sx, sy, ex, ey);
            }
            else 
            {
                if (grid[ex][ey]) captureSound.play();
                else moveSound.play();
                
                if (isPromote(sx, sy, ex, ey)) promote(sx, sy, ex, ey);
                else normalMove(sx, sy, ex, ey);
            }
        }

        resetEnPassant(sx, sy, ex, ey);

        return true;
    }
    return false;
}

void Board::makeHistory(int sx, int sy, int ex, int ey, std::shared_ptr<Piece> &piece)
{
    // Clear undo history
    while (!unHistory.empty()) unHistory.pop();

    // Create new history
    int moveValue = sx + sy * 10 + ex * 100 + ey * 1000 + grid[sx][sy]->hasMoved * 10000 + grid[sx][sy]->enPassant * 100000;
    history.push(std::make_pair(moveValue, piece));
}  

void Board::undo()
{
    if (history.empty()) return;
    std::pair <int, std::shared_ptr<Piece>> curUndo = history.top();
    history.pop();
    unHistory.push(curUndo);

    int sx = (curUndo.first) % 10,
        sy = (curUndo.first / 10) % 10,
        ex = (curUndo.first / 100) % 10,
        ey = (curUndo.first / 1000) % 10,
        castleState = (curUndo.first / 10000) % 10,
        enPassantState = (curUndo.first / 100000) % 10;

    std::cerr << sx << " " << sy << "\n";

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

    if (grid[sx][sy] && grid[sx][sy]->type == PAWN && abs(ex - sx) == 1 && abs(ey - sy) == 1 && !curUndo.second)
    {
        grid[ex][sy] = std::make_shared<Pawn>(!grid[sx][sy]->side);
        grid[ex][sy]->enPassant = 1;
    }

    if (grid[sx][sy] && grid[sx][sy]->type == KING) grid[sx][sy]->hasMoved = castleState;
    if (grid[sx][sy] && grid[sx][sy]->type == ROOK) grid[sx][sy]->hasMoved = castleState;
    if (grid[sx][sy] && grid[sx][sy]->type == PAWN) grid[sx][sy]->enPassant = enPassantState;

    turn = !turn;
    validMoves.clear();
}

void Board::redo()
{
    if (unHistory.empty()) return; 
    std::pair<int , std::shared_ptr<Piece>> curRedo = unHistory.top();
    unHistory.pop();
    history.push(curRedo);

    int sx = (curRedo.first)  % 10,
        sy = (curRedo.first / 10) % 10,
        ex = (curRedo.first / 100) % 10,
        ey = (curRedo.first / 1000) % 10;

    grid[ex][ey] = grid[sx][sy] ; 
    grid[sx][sy] = nullptr;
    
    if (grid[ex][ey] && grid[ex][ey]->type == KING && abs(sx - ex) == 2)
    {
        int rx = (ex > sx ? 7 : 0),   
            ry = sy,
            dx = (ex > sx ? 1 : -1);

        grid[ex][ey]->hasMoved = 1; 
        grid[rx][ry]->hasMoved = 1; 
        grid[sx + dx][sy] = grid[rx][ry];
        grid[rx][ry] = nullptr;
    }

    if (grid[ex][ey] && grid[ex][ey]->type == PAWN && abs(ex - sx) == 1 && abs(ey - sy) == 1 && !curRedo.second) 
        grid[ex][sy] = nullptr;

    turn = !turn;
    validMoves.clear();
}

Board::~Board() {};