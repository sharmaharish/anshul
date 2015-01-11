#include "values.hpp"
#include "Rook.hpp"
#include "Config.hpp"

using namespace std;

/**
 */
Rook::Rook(Color c, int p, Board& b, bool slide)
    : Piece(c, ROOK, Config::instance().rookValue(), p, (c == LITE)? " R" : "#R", slide, b)
{
    int ofs[4] = { -10, -1, 1, 10 };
    _offsets.assign(ofs, ofs + 4);
}

/**
 * Validates a move for the piece
 */
bool Rook::isMoveValid(const Move& m)
{
    int trow = Board::row(m._to);
    int tcol = Board::col(m._to);
    if (trow == row() || tcol == col())
        return Piece::isMoveValid(m);
    else
        return false;
}

/**
 * Moves the piece to the target position
 */
Piece* Rook::moveTo(int to)
{
    if (_color == LITE) {
        if (_place == H1) _board.revokeCastleRights(LITE_KING_SIDE);
        if (_place == A1) _board.revokeCastleRights(LITE_QUEEN_SIDE);
    }
    else {
        if (_place == H8) _board.revokeCastleRights(DARK_KING_SIDE);
        if (_place == A8) _board.revokeCastleRights(DARK_QUEEN_SIDE);
    }

    return Piece::moveTo(to);
}
