#include "King.hpp"

using namespace std;

/**
 * Constructor
 */
King::King(Color c, int p, Board& b)
    : Piece(c, KING, 0, p, (c == LITE) ? " K" : "#K", false, b)
    , _proxyBishop(c, p, b, false)
    , _proxyRook(c, p, b, false)
{
}

/**
 * Validates a move for the piece
 */
bool King::isMoveValid(const Move& m)
{
    if (m._type == NORMAL_MOVE || m._type == CAPTURE_MOVE)
        return _proxyBishop.isMoveValid(m) || _proxyRook.isMoveValid(m);
    else {
        if (_color == LITE && m._from == E1) {
            if (m._to == G1) {
                // check if intermediate squares are empty and not attacked
                if (_board.castleAllowed(LITE_KING_SIDE) &&
                    !_board[F1] && !_board[G1] &&
                    !_board.isUnderAttack(F1, DARK) &&
                    !_board.isUnderAttack(G1, DARK))
                {
                    return true;
                }
            }
            else if (m._to == C1) {
                // check if intermediate squares are empty and not attacked
                if (_board.castleAllowed(LITE_QUEEN_SIDE) &&
                    !_board[C1] && !_board[D1] &&
                    !_board.isUnderAttack(C1, DARK) &&
                    !_board.isUnderAttack(D1, DARK))
                {
                    return true;
                }
            }
        }
        else if (_color == DARK && _place == E8) {
            if (m._to == G8) {
                // check if intermediate squares are empty and not attacked
                if (_board.castleAllowed(DARK_KING_SIDE) &&
                    !_board[F8] && !_board[G8] &&
                    !_board.isUnderAttack(F8, LITE) &&
                    !_board.isUnderAttack(G8, LITE))
                {
                    return true;
                }
            }
            else if (m._to == C8) {
                // check if intermediate squares are empty and not attacked
                if (_board.castleAllowed(DARK_QUEEN_SIDE) &&
                    !_board[C8] && !_board[D8] &&
                    !_board.isUnderAttack(C8, LITE) &&
                    !_board.isUnderAttack(D8, LITE))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

/**
 * Generate moves for the piece
 */
void King::genMoves(MoveList& mlist)
{
    // generate castle move
    if (_color == LITE && _place == E1) {
        if (_board.castleAllowed(LITE_KING_SIDE) &&
            !_board[F1] && !_board[G1] &&
            !_board.isUnderAttack(F1, DARK) &&
            !_board.isUnderAttack(G1, DARK))
        {
            Move m(E1, G1, CASTLE_MOVE);
            mlist.push_back(m);
        }
        if (_board.castleAllowed(LITE_QUEEN_SIDE) &&
            !_board[C1] && !_board[D1] &&
            !_board.isUnderAttack(C1, DARK) &&
            !_board.isUnderAttack(D1, DARK))
        {
            Move m(E1, C1, CASTLE_MOVE);
            mlist.push_back(m);
        }
    }
    else if (_color == DARK && _place == E8) {
        if (_board.castleAllowed(DARK_KING_SIDE) &&
            !_board[F8] && !_board[G8] &&
            !_board.isUnderAttack(F8, LITE) &&
            !_board.isUnderAttack(G8, LITE))
        {
            Move m(E8, G8, CASTLE_MOVE);
            mlist.push_back(m);
        }
        if (_board.castleAllowed(DARK_QUEEN_SIDE) &&
            !_board[C8] && !_board[D8] &&
            !_board.isUnderAttack(C8, LITE) &&
            !_board.isUnderAttack(D8, LITE))
        {
            Move m(E8, C8, CASTLE_MOVE);
            mlist.push_back(m);
        }
    }

    _proxyBishop.genMoves(mlist);
    _proxyRook.genMoves(mlist);
}

/**
 * Generate capture moves for the piece
 */
void King::genCaptureMoves(MoveList& mlist)
{
    _proxyBishop.genCaptureMoves(mlist);
    _proxyRook.genCaptureMoves(mlist);
}

/**
 * Move the piece to the target location on the board
 */
Piece* King::moveTo(int to)
{
    if (_color == LITE)
        _board.revokeCastleRights(LITE_KING_SIDE | LITE_QUEEN_SIDE);
    else
        _board.revokeCastleRights(DARK_KING_SIDE | DARK_QUEEN_SIDE);

    return Piece::moveTo(to);
}

/**
 * Set the current position of the piece to the target position
 */
void King::setPlace(int to)
{
    _place = to;
    _proxyBishop.setPlace(to);
    _proxyRook.setPlace(to);
}

