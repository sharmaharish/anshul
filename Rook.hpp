#ifndef ROOK_HPP
#define ROOK_HPP

#include "Piece.hpp"

/**
 * Rook piece
 */
class Rook : public Piece
{
public:

    Rook(Color c, int p, Board& b, bool slide = true);

    virtual bool isMoveValid(const Move&);
    virtual Piece* moveTo(int to);
};

#endif // ROOK_HPP
