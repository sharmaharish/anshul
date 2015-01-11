#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "Piece.hpp"

/**
 */
class Knight : public Piece
{
public:

    Knight(Color c, int p, Board& b);

    virtual bool isMoveValid(const Move&);
};

#endif // KNIGHT_HPP
