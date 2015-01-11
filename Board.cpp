#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

#include "Queen.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Fen.hpp"

using namespace std;

/**
 * Prints the currest position of board.
 */
void Board::print() const
{
    string line = "   +---+---+---+---+---+---+---+---+\n";
    ostringstream brd;

    brd << "\n\n     A   B   C   D   E   F   G   H\n" << line;

    for (int i = BOARD_START; i < BOARD_END; ++i) {
        if (INIT_STATE[i] == 0)
            continue;

        int r = row(i);
        int c = col(i);

        if (r < 1 || r > 8) continue;
        if (c < 1 || c > 8) continue;

        if (c == 1)
            brd << " " << (char)(48 + r) << " ";

        if (_board[i] == 0)
            brd << "|   ";
        else
            brd << "|" << _board[i]->symbol() << " ";

        if (c == 8)
            brd << "|" << (char)(48 + r) << "\n" << line;
    }

    cout << brd.str() << "     A   B   C   D   E   F   G   H\n";
}

/**
 * Get fen string
 */
string Board::getFen() const
{
    ostringstream brd;
    int count = 0;

    for (int i = BOARD_START; i < BOARD_END; ++i) {
        if (INIT_STATE[i] == 0)
            continue;

        int r = row(i);
        int c = col(i);

        if (r < 1 || r > 8 || c < 1 || c > 8)
            continue;

        if (c == 1) {
            if (count != 0)
                brd << count;
            if (r != 8)
                brd << "/";
            count = 0;
        }

        if (_board[i] == 0) {
            count++;
        }
        else if (count > 0) {
            brd << count << _board[i]->symbol();
            count = 0;
        }
        else {
            brd << _board[i]->symbol();
        }

        if (c == 8 && r == 1 && count > 0)
            brd << count;
    }

    return brd.str();
}

/**
 * Finds a piece of given color and rank from the ones that were
 * taken off the board before and returns it.
 * @return pointer to a Piece object
 */
Piece* Board::getPiece(Color c, Rank r, int pos)
{
    PieceList& plist = getPieceList(c);

    PieceList::iterator it  = plist.begin();
    PieceList::iterator end = plist.end();

    for (; it != end; ++it) {
        Piece* p = *it;
        if (p && p->notLive() && p->rank() == r) {
            p->setPlace(pos);
            p->setLive(true);
            return p;
        }
    }

    Piece* p = 0;
    //
    // a piece of this rank was not taken ... it needs to be created newly
    //
    switch (r)
    {
        case QUEEN:
            p = new Queen(c, pos, *this);
            break;
        case ROOK:
            p = new Rook(c, pos, *this);
            break;
        case BISHOP:
            p = new Bishop(c, pos, *this);
            break;
        case KNIGHT:
            p = new Knight(c, pos, *this);
            break;
        case PAWN:
        case KING:
        default:
            assert(false);
    }

    assert(p);
    plist.push_back(p);

    return p;
}

/**
 * Tests if a board square is under attack by any opponent piece
 * @return boolean
 */
bool Board::isUnderAttack(int p, Color side)
{
    PieceBoard::iterator it = _board.begin();
    PieceBoard::iterator end = _board.end();

    for (; it != end; ++it) {
        Piece* pc = *it;
        if (pc && (pc->color() == side)) {
            Move m(pc->place(), p);
            if (pc->isMoveValid(m))
                return true;
        }
    }

    return false;
}

/**
 * Constructor
 */
Board::Board()
    : _castleRights(INITIAL_RIGHTS)
    , _epSq(-1)
{
    init();
}

/**
 */
void Board::init(const string& str)
{
    _castleRights = INITIAL_RIGHTS;
    _epSq = -1;

    Fen fen(str);
    for (size_t i = 0; i < _board.size(); ++i) {
        Piece* ptr = _board[i] = fen.getPiece(i, this);
        if (!ptr)
            continue;
        if (ptr->rank() == KING)
            _kings[ptr->color()] = ptr;
        switch (ptr->color()) {
            case LITE:
                _litePieces.push_back(ptr);
                break;
            case DARK:
                _darkPieces.push_back(ptr);
                break;
            default:
                assert(false && "Invalid piece color.");
                break;
        }
    }
}
