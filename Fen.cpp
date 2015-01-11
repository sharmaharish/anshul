#include <cstdlib>
#include <sstream>

#include "Fen.hpp"
#include "Board.hpp"
#include "Piece.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "King.hpp"
#include "Queen.hpp"

using namespace std;

namespace {

/**
 * Tokenize the given text line and delimiter string
 */
void tokenize(const string& str,const string& delimiters, vector<string>& tokens)
{
    // skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);

    // find first "non-delimiter".
    string::size_type pos = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos) {
        // found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}

}

/**
 * Constructor
 */
Fen::Fen(const string& fen)
{
    parse(fen);
}

/**
 *
 */
int Fen::translate(int i) const
{
    if (!INIT_STATE[i])
        return 64;

    const int row = 8 - Board::row(i);
    const int col = Board::col(i) - 1;

    const int ret = row * 8 + col;
    assert(ret >= 0 && ret < 64);

    return ret;
}

/**
 * Piece factory method
 */
Piece* Fen::getPiece(int i, Board* brd) const
{
    assert(_tokens.size() == 6);
    assert(_tokens[0].size() == 65);

    Piece* ptr = 0;
    const char c = _tokens[0][translate(i)];
    Color clr = (c < 97)? LITE : DARK;

    switch (c) {
        case 'r':
        case 'R':
            ptr = new Rook(clr, i, *brd);
            break;
        case 'n':
        case 'N':
            ptr = new Knight(clr, i, *brd);
            break;
        case 'b':
        case 'B':
            ptr = new Bishop(clr, i, *brd);
            break;
        case 'q':
        case 'Q':
            ptr = new Queen(clr, i, *brd);
            break;
        case 'k':
        case 'K':
            ptr = new King(clr, i, *brd);
            break;
        case 'p':
        case 'P':
            ptr = new Pawn(clr, i, *brd);
            break;
        case '.':
        default:
            break;
    }

    assert(ptr || c == '.');

    return ptr;
}

/**
 *
 */
Color Fen::turn() const
{
    assert(_tokens.size() == 6);
    assert(_tokens[1].size() == 1);
    return (_tokens[1][0] == 'w')? LITE : DARK;
}

/**
 *
 */
byte Fen::castleRights() const
{
    assert(_tokens.size() == 6);
    return byte(0);
}

/**
 *
 */
int Fen::epSquare() const
{
    assert(_tokens.size() == 6);
    const string& sq = _tokens[3];
    if (sq == "-")
        return -1;
    else
        return Board::alg2ord(sq.c_str());
}

/**
 *
 */
int Fen::halfMoves() const
{
    assert(_tokens.size() == 6);
    return STR_TO_INT(_tokens[4].c_str());
}

/**
 *
 */
int Fen::moves() const
{
    assert(_tokens.size() == 6);
    return STR_TO_INT(_tokens[5].c_str());
}

/**
 * Parse the FEN string
 */
void Fen::parse(const string& str)
{
    tokenize(str, " ", _tokens);
    assert(!_tokens.empty());

    // board position
    vector<string> brd_pos;
    tokenize(_tokens[0], "/", brd_pos);

    ostringstream fen;
    vector<string>::const_iterator oit = brd_pos.begin();
    vector<string>::const_iterator oend = brd_pos.end();
    for (; oit != oend; ++oit) {
        const string& t = *oit;
        const size_t iend = t.size();
        for (size_t i = 0; i < iend; ++i) {
            const char c = t[i];
            if (isdigit(c)) {
                int cnt = CHAR_TO_INT(c);
                for (int i = 0; i < cnt; ++i)
                    fen << '.';
            }
            else {
                fen << c;
            }
        }
    }

    fen << '.';
    _tokens[0] = fen.str();

    assert(_tokens[0].size() == 65);
}
