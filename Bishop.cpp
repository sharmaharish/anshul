#include "Bishop.hpp"
#include "Config.hpp"
#include "values.hpp"

using namespace std;

/**
 * Constructor
 */
Bishop::Bishop(Color c, int p, Board& b, bool slide)
    : Piece(c, BISHOP, Config::instance().bishopValue(), p, (c == LITE)? " B" : "#B", slide, b)
{
    int ofs[4] = { -11, -9, 9, 11 };
    _offsets.assign(ofs, ofs + 4);

    PlaceValues pv = { BISHOP_PLACE_VALUES };

    for (size_t i = 0; i < pv.size(); ++i)
        _values[i] = (_color == LITE)? pv[i] : pv[Board::flip(i)];
}

/**
 * Validates a move.
 * @returns boolean
 */
bool Bishop::isMoveValid(const Move& m)
{
    return Piece::isMoveValid(m);
}

