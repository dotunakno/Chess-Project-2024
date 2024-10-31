#include<iostream>
#include<string>
#include<vector>
#include<stdio.h>
#include<stack>
#include<memory>
#include<thread>
#include<chrono>
#include "Pieces.h"
#include "Board.h"
#include <boost/process.hpp>
namespace bp = boost::process;

class StockFish
{
private:
    std::string ToUCI(int sx , int sy , int ex , int ey );
    std::string runStockfishCommand(const std::string& command) ;
    std::string ConstructUci(std::stack<std::pair<int, std::shared_ptr<Piece> > > History);
    std::tuple<int,int,int,int> ConstructTuple(std::string uci);
    std::string GetResponse();
    bp::opstream stockfish_in;
    bp::ipstream stockfish_out;
    std::unique_ptr<bp::child> stockfish;
public:
    StockFish();
    ~StockFish(); 


    std::tuple<int,int,int,int> FindBest(std::stack<std::pair<int, std::shared_ptr<Piece> > > History);
};