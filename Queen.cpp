#include "Queen.hpp"
#include "Config.hpp"

using namespace std;

/**
 */
Queen::Queen(Color c, int p, Board& b)
    : Piece(c, QUEEN, Config::instance().queenValue(), p, (c == LITE)? " Q" : "#Q", true, b)
    , _proxyBishop(c, p, b)
    , _proxyRook(c, p, b)
{
}

/**
 * Validates a move for the piece
 */
bool Queen::isMoveValid(const Move& m)
{
    return _proxyBishop.isMoveValid(m) || _proxyRook.isMoveValid(m);
}

/**
 * Generate non-capture moves for the piece
 */
void Queen::genMoves(MoveList& mlist)
{
    _proxyBishop.genMoves(mlist);
    _proxyRook.genMoves(mlist);
}

/**
 * Generate capture moves for the piece
 */
void Queen::genCaptureMoves(MoveList& mlist)
{
    _proxyBishop.genCaptureMoves(mlist);
    _proxyRook.genMoves(mlist);
}

/**
 * Set the current position of the piece to target position
 */
void Queen::setPlace(int to)
{
    _place = to;
    _proxyBishop.setPlace(to);
    _proxyRook.setPlace(to);
}

