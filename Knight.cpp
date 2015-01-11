#include "Knight.hpp"
#include "Config.hpp"
#include "values.hpp"

using namespace std;

/**
 * Constructor
 */
Knight::Knight(Color c, int p, Board& b)
    : Piece(c, KNIGHT, Config::instance().knightValue(), p, (c == LITE)? " N" : "#N", false, b)
{
    int ofs[8] = { -21, -19, -12, -8, 8, 12, 19, 21 };
    _offsets.assign(ofs, ofs + 8);

    PlaceValues pv = { KNIGHT_PLACE_VALUES };

    for (size_t i = 0; i < pv.size(); ++i)
        _values[i] = (_color == LITE)? pv[i] : pv[Board::flip(i)];
}

/**
 * Validates a move for the piece
 */
bool Knight::isMoveValid(const Move& m)
{
    if (_board[m._to] && _board[m._to]->color() == _color)
        return false;

    int ofs = m._to - m._from;

    Offsets::const_iterator it = _offsets.begin();
    Offsets::const_iterator end = _offsets.end();
    for (; it != end; ++it) {
        if (ofs == *it)
            return true;
    }

    return false;
}

