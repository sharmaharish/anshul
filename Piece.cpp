#include "Piece.hpp"

using namespace std;

/**
 */
Piece::Piece(Color c, Rank r, int v, int p, cstr sym, bool s, Board& b)
    : _color(c)
    , _rank(r)
    , _slide(s)
    , _live(true)
    , _place(p)
    , _value(v)
    , _board(b)
    , _symbol(sym)
{
}

/**
 * Validates a move for the piece
 */
bool Piece::isMoveValid(const Move& m)
{
    if (m._from != _place)
        return false;

    Offsets::iterator it  = _offsets.begin();
    Offsets::iterator end = _offsets.end();

    for (; it != end; ++it) {
        for (int t = _place + *it; _board.state(t) != 0; t += *it) {
            if (t == m._to)
                return (!_board[t] || _board[t]->color() != _color);
            if (_slide == false || _board[t])
                break;
        }
    }

    return false;
}

/**
 * Checks to see if the piece is under attack
 */
bool Piece::isUnderAttack()
{
    PieceList& pl = _board.getPieceList(_color == LITE ? DARK : LITE);

    PieceList::iterator it  = pl.begin();
    PieceList::iterator end = pl.end();

    for (; it != end; ++it) {
        Piece* p = *it;
        if (p && p->live()) {
            Move m(p->place(), _place);
            if (p->isMoveValid(m))
                return true;
        }
    }

    return false;
}

/**
 * Generate non-capture moves for the piece
 */
void Piece::genMoves(MoveList& mlist)
{
    Offsets::iterator it = _offsets.begin();
    Offsets::iterator end = _offsets.end();

    for (; it != end; ++it) {
        int to = _place + *it;
        for (;_board.state(to) != 0 && _board[to] == 0; to += *it) {
            Move m(_place, to);
            mlist.push_back(m);
            if (_slide == false)
                break;
        }
    }
}

/**
 * Generate capture moves for the piece
 */
void Piece::genCaptureMoves(MoveList& mlist)
{
    Offsets::iterator it = _offsets.begin();
    Offsets::iterator end = _offsets.end();

    for (; it != end; ++it) {
        for (int to = _place + *it; _board.state(to) != 0; to += *it) {
            if (_board[to] && _board[to]->color() != _color) {
                Move m(_place, to, CAPTURE_MOVE, _board[to]);
                mlist.push_back(m);
                break;
            }
            if (_slide == false || _board[to])
                break;
        }
    }
}

/**
 * Move the piece to the target position on the board
 */
Piece* Piece::moveTo(int to)
{
    Piece* p       = _board[to];
    _board[to]     = _board[_place];
    _board[_place] = 0;

    setPlace(to);

    if (p)
        p->setLive(false);

    return p;
}


