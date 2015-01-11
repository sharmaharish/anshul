#ifndef KING_HPP
#define KING_HPP

#include "Bishop.hpp"
#include "Rook.hpp"

/**
 * King piece
 */
class King : public Piece
{
public:

    King(Color c, int p, Board& b);

    virtual bool isMoveValid(const Move& m);

    virtual void genMoves(MoveList&);
    virtual void genCaptureMoves(MoveList&);

    virtual void setPlace(int to);
    virtual Piece* moveTo(int to);

private:

    Bishop _proxyBishop;
    Rook   _proxyRook;
};

#endif // KING_HPP
