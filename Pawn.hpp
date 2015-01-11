#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"

/**
 * Pawn piece
 */
class Pawn : public Piece
{
public:

    Pawn(Color c, int p, Board& b);

    virtual bool isMoveValid(const Move&);

    virtual void genMoves(MoveList& mlist);
    virtual void genCaptureMoves(MoveList& mlist);
};

#endif // PAWN_HPP
