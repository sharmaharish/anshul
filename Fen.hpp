#ifndef FEN_HPP
#define FEN_HPP

#include <vector>
#include <string>

#include "common.hpp"
#include "constants.hpp"

class Piece;
class Board;

/**
 * Forsyth Edwards Notation
 */
class Fen
{
public:

    explicit Fen(const std::string& fen);

    Piece* getPiece(int i, Board* brd) const;

    Color turn() const;
    byte  castleRights() const;
    int   epSquare() const;
    int   halfMoves() const;
    int   moves() const;

private:

    void parse(const std::string&);
    int translate(int i) const;

private:

    MAKE_NONCOPYABLE(Fen);

    std::vector<std::string> _tokens;
};

#endif // FEN_HPP
