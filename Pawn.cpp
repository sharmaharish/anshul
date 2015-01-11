#include "Pawn.hpp"
#include "Config.hpp"
#include "values.hpp"

using namespace std;

/**
 */
Pawn::Pawn(Color c, int p, Board& b)
    : Piece(c, PAWN, Config::instance().pawnValue(), p, (c == LITE)? " P" : "#P", false, b)
{
    int ofs[4] = { 9, 11, 10, 20 };
    if (_color == LITE) {
        for (int i = 0; i < 4; ++i)
            ofs[i] *= -1;
    }

    _offsets.assign(ofs, ofs + 4);

    PlaceValues pv = { PAWN_PLACE_VALUES };

    for (size_t i = 0; i < pv.size(); ++i)
        _values[i] = (c == LITE)? pv[i] : pv[Board::flip(i)];
}

/**
 * Validates a move for the piece
 */
bool Pawn::isMoveValid(const Move& m)
{
    MoveList ml;
    genMoves(ml);

    MoveList::iterator it = ml.begin();
    MoveList::iterator end = ml.end();
    for (; it != end; ++it) {
        if (*it == m)
            return true;
    }

    ml.clear();
    genCaptureMoves(ml);

    it = ml.begin();
    end = ml.end();
    for (; it != end; ++it) {
        if (*it == m)
            return true;
    }

    return false;
}

/**
 * Generates non-capture moves for the piece
 */
void Pawn::genMoves(MoveList& mlist)
{
    const int from = _place;

    Offsets::const_iterator it = _offsets.begin();
    Offsets::const_iterator end = _offsets.end();
    for (; it != end; ++it) {
        const int ofs = *it;
        if (ofs % 10 != 0) // we don't want to check for capture moves
            continue;

        const int to = from + ofs;
        if (!_board.state(to) || _board[to])
            continue;

        const int frow = Board::row(from);
        const int trow = Board::row(to);
        const int rdiff = abs(frow - trow);

        MoveType flags = NORMAL_MOVE;
        if (rdiff == 2) { // double pawn move
            if (_color == LITE && frow != 2)
                continue;
            if (_color == DARK && frow != 7)
                continue;

            const int mid = (from + to) / 2;
            if (_board[mid])
                continue;

            flags = PAWN_DOUBLE_MOVE;
        }
        else if ((_color == LITE && trow == 8) && (_color == DARK && trow == 1))
            flags = PROMOTE_MOVE;

        Move m(from, to, flags);
        mlist.push_back(m);
    }
}

/**
 * Generates capture moves for the piece
 */
void Pawn::genCaptureMoves(MoveList& mlist)
{
    const int from = _place;

    Offsets::const_iterator it = _offsets.begin();
    Offsets::const_iterator end = _offsets.end();
    for (; it != end; ++it) {
        const int ofs = *it;
        const int to = from + ofs;
        if (ofs % 10 == 0) // we don't want to check for non-capture moves
            continue;
        if (!_board.state(to))
            continue;
        if (!_board[to]) {
            if (_board.epSq() == to) {
                Move m(from, to, ENPASSE_MOVE);
                mlist.push_back(m);
            }
        }
        else if (_board[to]->color() != _color) {
            Move m(from, to, CAPTURE_MOVE);
            mlist.push_back(m);
        }
    }
}
