#include "AI.h"

StockFish::StockFish()
{
    stockfish = std::make_unique<bp::child>("D:\\SchoolHcmus\\Project\\Chess-Project-2024\\Menu_copy\\Stockfish\\stockfish-windows-x86-64-avx2.exe",bp::std_out > stockfish_out , bp::std_in < stockfish_in);
    
}

StockFish::~StockFish()
{
    if(stockfish && stockfish->running()) stockfish->terminate();
}

std::string StockFish::ToUCI(int sx , int sy , int ex , int ey )
{
    std::string Uci = "";
    Uci += ('a' + sx);
    Uci += ('1' + 7-sy);
    Uci += ('a' + ex) ; 
    Uci += ('1' + 7-ey) ;
    return Uci;
}




std::string StockFish::ConstructUci(std::stack<std::pair<int, std::shared_ptr<Piece> > > History)
{
    std::stack<int> MoveList ; 
    while(!History.empty())
    {
        MoveList.push(History.top().first);
        History.pop();
    }
    std::string uciPosition = "position startpos moves";

    while(!MoveList.empty())
    {
        int sx = MoveList.top() % 10 ,
            sy = (MoveList.top()/10)%10 ,
            ex = (MoveList.top()/100)%10 ,
            ey = (MoveList.top()/1000)%10 ;
        uciPosition += " " + ToUCI(sx,sy,ex,ey);
        MoveList.pop();
    }
    return uciPosition;
}

std::tuple<int,int,int,int> StockFish::ConstructTuple(std::string uci)
{
    if(uci.size() < 4)
    {

        return std::make_tuple(-1,-1,-1,-1) ; 
    }
    int sx = (uci[0] - 'a'),
        sy = 7-(uci[1] - '1'),
        ex = (uci[2] - 'a'), 
        ey = 7-(uci[3] - '1');
    return std::make_tuple(sx,sy,ex,ey);
}

std::string StockFish::GetResponse() {
    std::string line, response;
    while (std::getline(stockfish_out, line)) {
        std::cout << "Stockfish output: " << line << '\n';
        response += line + "\n";
        if (line.find("uciok") != std::string::npos || line.find("bestmove") != std::string::npos) {
            break;  
        }
    }
    return response;
}

std::tuple<int,int,int,int> StockFish::FindBest(std::stack<std::pair<int, std::shared_ptr<Piece> > > History)
{
    std::string UciPosition = ConstructUci(History);
    stockfish_in << "uci" << std::endl;
    GetResponse();
      
    stockfish_in << UciPosition << std::endl;
    stockfish_in << "go depth 10" << std::endl;
    
    std::string Response = GetResponse(),
                Bestmove = Response.substr(Response.find("bestmove") + 9 , 4) ; 
    return ConstructTuple(Bestmove);
}