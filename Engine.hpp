#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <fstream>
#include <string>

#include "Board.hpp"
#include "types.hpp"

#define INFINITY 999999

/**
 * Engine class which defines all the move computation logic and also provides
 * interface for xboard protocol.
 */
class Engine
{
public:

    Engine();

    void test(const std::string&);
    void play();
    void xboard();

private:

    bool getBookMove(Move&);
    std::string getPlayedMoves();

    bool validateMove(const Move&);
    void setType(Move& mov);

    bool makeMove(Move&);
    void unmakeMove();

    bool think();
    int  search(int ply, int depth, int alpha, int beta);

    bool genMoves(MoveList&);

    int  evaluate();

    void printDiagnosticInfo();

private:

    Color         _self;                  // engine's side
    Color         _turn;                  // side to play next move
    Color         _rival;                 // rival with respect to _turn

    Board         _board;

    MoveList      _moves;
    MoveList      _movesPlayed;
    MoveList      _pvMoves;
    Move          _bestMove;

    std::ifstream _book;
};

#endif // ENGINE_HPP
