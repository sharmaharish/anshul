#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "Bishop.hpp"
#include "Rook.hpp"

/**
 */
class Queen : public Piece
{
public:

    Queen(Color c, int p, Board& b);

    virtual bool isMoveValid(const Move& m);

    virtual void genMoves(MoveList&);
    virtual void genCaptureMoves(MoveList&);

    virtual void setPlace(int to);

private:

    Bishop _proxyBishop;
    Rook   _proxyRook;
};

#endif // QUEEN_HPP
