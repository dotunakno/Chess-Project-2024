#include<iostream>
#include<memory>
#include<vector>
#include<math.h>
enum Color {WHITE,BLACK};

class Piece
{
    public:
    int EnPa = 0 ;
    Color color ;
    Piece(Color color) : color(color) {};
    virtual bool IsValidMove(int sx,int sy,int ex,int ey,
                              std::vector<std::vector<std::shared_ptr<Piece>>>& grid) = 0 ;
    virtual char GetSymbol() = 0 ;


};

class Pawn : public Piece
{
    public:
    Pawn(Color color) : Piece(color){}
    bool IsValidMove(int sx, int sy , int ex , int ey,
                      std::vector<std::vector<std::shared_ptr<Piece> > >& grid) override
    {
        if(grid[ex][ey] && grid[ex][ey]->color == color) return false ;
        if(abs(sx-ex) == 1 && abs(ey-sy) == 1)
        {
            int Direction = (color == WHITE ? 1 : -1 );

            if(grid[ex][ey]) return ey - sy == Direction ;
            else if( grid[ex][sy] && grid[ex][sy]->EnPa )
            {
                grid[ex][sy] = nullptr;
                return true ;
            }
            return false ;
        }
        if(color == WHITE)
        {
            int Direction = (sy == 1 ? 2 : 1 );
            if(grid[ex][ey] ||  grid[sx][sy+1]) return false ;
            return sx == ex && sy < ey && ey <= sy + Direction;
        } else
        {

            int Direction = (sy == 6 ? -2:-1) ;

            if(grid[ex][ey] ||  grid[sx][sy-1]) return false ;
            return sx == ex && sy + Direction <= ey && ey < sy;
        }
    }
    char GetSymbol() override
    {
        if(color == BLACK) return 'p';
        else return 'P';
    }
};


class Knight : public Piece
{
public:
    Knight(Color color): Piece(color){}
    int KnightMoveX[8] = {1,1,2,2,-1,-1,-2,-2},
        KnightMoveY[8] = {2,-2,1,-1,2,-2,1,-1};
    bool IsValidMove (int sx , int sy , int ex , int ey,
                      std::vector<std::vector<std::shared_ptr<Piece>>>& grid ) override
    {
        if(grid[ex][ey] && grid[ex][ey]->color == color) return false ;
        for (int i = 0 ; i < 8 ; i++)
        {
            int nx = sx + KnightMoveX[i] ,
                ny = sy + KnightMoveY[i] ;
            if(nx == ex && ny == ey) return true;
        }
        return false ;
    }
    char GetSymbol() override
    {
        return (color == WHITE ? 'N' : 'n');
    }
};

class Bishop : public Piece
{
public:
    Bishop(Color color) : Piece(color){}

    bool IsValidMove(int sx, int sy , int ex , int ey ,
                     std::vector<std::vector<std::shared_ptr<Piece>>>& grid) override
    {
        // Basic check
        if(grid[ex][ey] && grid[ex][ey]->color == color) return false ;
        if(abs(sx - ex ) != abs(sy-ey)) return false ;
        // Check on the way
        int DirX = ( ex - sx ) > 0 ? 1 : -1 ,
            DirY = ( ey - sy ) > 0 ? 1 : -1 ;
        sx += DirX;
        sy += DirY;

        while(sx != ex && sy != ey){
            if(grid[sx][sy]) return false ;
            sx += DirX;
            sy += DirY;
        }
        return true ;
    }

    char GetSymbol() override
    {
        return color == WHITE? 'B':'b' ;
    }
};
class Rook : public Piece
{
public:
    Rook(Color color) : Piece(color){}
    bool IsValidMove(int sx, int sy , int ex , int ey,
                    std::vector<std::vector<std::shared_ptr<Piece> > >& grid) override{
            // Basic check

            if(grid[ex][ey] && grid[ex][ey]->color == color) return false ;
            if(sx != ex && sy != ey) return false ;
            // Check on way
            int DirX = 0 ,
                DirY = 0 ;
            if(sy != ey) DirY = (ey-sy) > 0 ? 1 : -1 ;
            else DirX = (ex - sx ) > 0 ? 1 : - 1 ;

            sx += DirX ;
            sy += DirY ;

            while(sx != ex || sy != ey)
            {
                if(grid[sx][sy]) return false;
                sx += DirX ;
                sy += DirY ;
            }
            return true ;
        }

    char GetSymbol() override{
        return color == WHITE ? 'R' : 'r' ;
    }
};

class Queen : public Piece
{
public:
    Queen(Color color) : Piece(color) {};
     bool IsValidMove(int sx, int sy , int ex , int ey,
                    std::vector<std::vector<std::shared_ptr<Piece> > >& grid) override{
        // Basic Check
        if(grid[ex][ey] && grid[ex][ey]->color == color) return false ;

        if(abs(sx - ex ) == abs(sy- ey) || sx == ex || ey == sy)
        {
            int DirX = 0 ,
                DirY = 0 ;
            if(ex - sx != 0 ) DirX = (ex-sx) > 0 ? 1 : - 1 ;
            if(ey - sy != 0 ) DirY = (ey-sy) > 0 ? 1 : - 1 ;
            sx += DirX ;
            sy += DirY ;
            while(sx != ex || sy != ey)
            {
                if(grid[sx][sy]) return false ;
                sx += DirX ;
                sy += DirY ;
            }
            return true ;;
        } else return false ;

    }
    char GetSymbol() override{
        return color == WHITE ? 'Q' : 'q';
    }
};

class King : public Piece
{
private:
    // 8 direction of a king movement
    int DirX[8] = {1,1,-1,-1,0,0,1,-1},
        DirY[8] = {1,-1,1,-1,1,-1,0,0};
public:
    King(Color color): Piece(color){};

    bool IsValidMove(int sx, int sy , int ex , int ey,
                    std::vector<std::vector<std::shared_ptr<Piece> > >& grid) override{
        // Basic check
        if(grid[ex][ey] && grid[ex][ey]->color == color) return false ;
        // Try every move to find match for ex and ey
        for(int i = 0 ; i < 8 ; i ++ )
        {
            // calculate next x and next y
            int nx = sx + DirX[i] ,
                ny = sy + DirY[i] ;
            if(nx == ex && ny == ey) return true ;
        }
        return false  ;
    }

    char GetSymbol() override
    {
        return color == WHITE ? 'K' : 'k';
    }
};

class Board
{
private:
    std::vector<std::vector<std::shared_ptr<Piece> > > grid ;

    bool CheckKing(int sx , int sy , int ex , int ey ,Color color){
        // Make a virtual board
        bool IsInChecked = 0 ;
        std::shared_ptr<Piece> tmp_piece = grid[ex][ey] ;
        grid[ex][ey] = grid[sx][sy] ;
        grid[sx][sy] = nullptr;
        int KingX =0 ,
            KingY =0 ;
        for(int i = 0 ; i < 8 ; i ++)
            for(int j = 0 ; j < 8 ; j ++ )
                if(color == WHITE)
                {
                    if(grid[i][j] && grid[i][j]->GetSymbol() == 'K')
                    {
                        KingX = i ;
                        KingY = j ;
                        break ;
                    }
                } else if(grid[i][j] && grid[i][j]->GetSymbol() == 'k')
                {
                    KingX = i ;
                    KingY = j ;
                    break ;
                }
        for(int i = 0 ; i < 8 ; i ++ )
            for(int j = 0 ; j < 8 ; j ++ )
                if(grid[i][j] && grid[i][j]->color != color && grid[i][j]->IsValidMove(i,j,KingX,KingY,grid )) IsInChecked = 1 ;
        // Back to real board
        grid[sx][sy] = grid[ex][ey] ;
        grid[ex][ey] = tmp_piece;
        return !IsInChecked;
    }

public:
    Board()
    {
        grid.resize(8,std::vector<std::shared_ptr<Piece> > (8,nullptr));
        initializerBoard();
    }

    void initializerBoard()
    {
        // Pawn Setup
        for (int i = 0 ; i < 8; i ++){
            grid[i][1] = std::make_shared<Pawn> (WHITE);
            grid[i][6] = std::make_shared<Pawn> (BLACK);
        }
        // Knight setup
        grid[6][0] = std::make_shared<Knight> (WHITE);
        grid[1][0] = std::make_shared<Knight> (WHITE);
        grid[1][7] = std::make_shared<Knight> (BLACK);
        grid[6][7] = std::make_shared<Knight> (BLACK);
        // Bishop setup
        grid[2][0] = std::make_shared<Bishop> (WHITE);
        grid[5][0] = std::make_shared<Bishop> (WHITE);
        grid[2][7] = std::make_shared<Bishop> (BLACK);
        grid[5][7] = std::make_shared<Bishop> (BLACK);
        // Rook  setup
        grid[0][0] = std::make_shared<Rook> (WHITE);
        grid[7][0] = std::make_shared<Rook> (WHITE);
        grid[0][7] = std::make_shared<Rook> (BLACK);
        grid[7][7] = std::make_shared<Rook> (BLACK);
        // Queen setup
        grid[4][0] = std::make_shared<Queen> (WHITE);
        grid[4][7] = std::make_shared<Queen> (BLACK);
        // King setup
        grid[3][0] = std::make_shared<King> (WHITE);
        grid[3][7] = std::make_shared<King> (BLACK);
    }
    void ResetEnpa()
    {
        for(int i = 0 ; i< 8 ; i ++)
            for(int j = 0 ; j < 8 ; j ++)
                if(grid[i][j] && (grid[i][j]->GetSymbol() == 'P' || grid[i][j] ->GetSymbol() =='p') )
                {
                    grid[i][j]->EnPa = 0 ;
                }
    }
    bool MovePiece(int sx,int sy, int ex , int ey )
    {

        if(grid[sx][sy] && CheckKing(sx,sy,ex,ey,grid[sx][sy]->color)
           && grid[sx][sy]->IsValidMove(sx,sy,ex,ey,grid))
        {
            ResetEnpa();
            grid[ex][ey] = grid[sx][sy] ;
            grid[sx][sy]= nullptr;
            if((grid[ex][ey]->GetSymbol() == 'P' || grid[ex][ey] ->GetSymbol() =='p')
               && abs(ey - sy) == 2) grid[ex][ey]->EnPa = 1 ;
            return true ;
        } else std::cout << "Invalid move\n";
        return false ;
    }

    void PrintBoard()
    {
        for(int i = 0 ; i < 8 ; i++ ){
            for (int j = 0 ; j < 8 ; j ++)
                if(grid[j][i])
                {
                    std::cout << grid[j][i]->GetSymbol();
                } else std::cout << ".";
            std::cout << '\n' ;
        }
    }
};

Board MainBoard ;

int main(){
    MainBoard.PrintBoard();
    while (true)
    {
        using namespace std;
        cout << "Input the move ( sx , sy , ex ,ey ) : ";
        int sx , sy ,ex,ey ;
        cin >> sx >> sy >> ex >> ey  ;
        MainBoard.MovePiece(sx,sy,ex,ey);
        MainBoard.PrintBoard();
        cout << "----------------------------------\n";
    }
    return 0 ;
}
