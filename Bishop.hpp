#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "Piece.hpp"

/**
 * Bishop piece
 */
class Bishop : public Piece
{
public:

    Bishop(Color c, int p, Board& b, bool slide = true);

    virtual bool isMoveValid(const Move&);
};

#endif // BISHOP_HPP
