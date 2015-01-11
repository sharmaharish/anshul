#ifndef BOARD_HPP
#define BOARD_HPP

#include <cstring>
#include <cassert>

#include "types.hpp"

/**
 *                                                      A   B   C   D   E   F   G   H
 *  +---+---+---+---+---+---+---+---+---+---+     +---+---+---+---+---+---+---+---+---+---+
 *  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |     | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
 *  +---+---+---+---+---+---+---+---+---+---+     +---+---+---+---+---+---+---+---+---+---+
 *  | 10| 11| 12| 13  14| 15| 16| 17| 18| 19|     | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
 *  +---+---+---+---+---+---+---+---+---+---+     +---+---+---+---+---+---+---+---+---+---+
 *  | 20| 21| 22| 23| 24| 25| 26| 27| 28| 29|   8 | 0 |#R |#N |#B |#Q |#K |#B |#N |#R | 0 |
 *  +---+---+---+---+---+---+---+---+---+---+     +---+---+---+---+---+---+---+---+---+---+
 *  | 30| 31| 32| 33| 34| 35| 36| 37| 38| 39|   7 | 0 |#p |#p |#p |#p |#p |#p |#p |#p | 0 |
 *  +---+---+---+---+---+---+---+---+---+---+     +---+---+---+---+---+---+---+---+---+---+
 *  | 40| 41| 42| 43| 44| 45| 46| 47| 48| 49|   6 | 0 |   |   |   |   |   |   |   |   | 0 |
 *  +---+---+---+---+---+---+---+---+---+---+     +---+---+---+---+---+---+---+---+---+---+
 *  | 50| 51| 52| 53| 54| 55| 56| 57| 58| 59|   5 | 0 |   |   |   |   |   |   |   |   | 0 |
 *  +---+---+---+---+---+---+---+---+---+---+     +---+---+---+---+---+---+---+---+---+---+
 *  | 60| 61| 62| 63| 64| 65| 66| 67| 68| 69|   4 | 0 |   |   |   |   |   |   |   |   | 0 |
 *  +---+---+---+---+---+---+---+---+---+---+     +---+---+---+---+---+---+---+---+---+---+
 *  | 70| 71| 72| 73| 74| 75| 76| 77| 78| 79|   3 | 0 |   |   |   |   |   |   |   |   | 0 |
 *  +---+---+---+---+---+---+---+---+---+---+     +---+---+---+---+---+---+---+---+---+---+
 *  | 80| 81| 82| 83| 84| 85| 86| 87| 88| 89|   2 | 0 | p | p | p | p | p | p | p | p | 0 |
 *  +---+---+---+---+---+---+---+---+---+---+     +---+---+---+---+---+---+---+---+---+---+
 *  | 90| 91| 92| 93| 94| 95| 96| 97| 98| 99|   1 | 0 | R | N | B | Q | K | B | N | R | 0 |
 *  +---+---+---+---+---+---+---+---+---+---+     +---+---+---+---+---+---+---+---+---+---+
 *  |100|101|102|103|104|105|106|107|108|109|     | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
 *  +---+---+---+---+---+---+---+---+---+---+     +---+---+---+---+---+---+---+---+---+---+
 *  |110|111|112|113|114|115|116|117|118|119|     | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
 *  +---+---+---+---+---+---+---+---+---+---+     +---+---+---+---+---+---+---+---+---+---+
 *
 */

#define INIT_POSITION_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0"

/**
 * Board representation
 */
class Board
{
public:

    static int col(int p)  {
        return p % 10;
    }

    static int row(int p) {
        return 10 - p / 10;
    }

    static int alg2ord(const char* sq) {
        assert(sq && strlen(sq) >= 2);
        return (10 * (58 - sq[1]) + (tolower(sq[0]) - 96));
    }

    static int flip(int p) {
        int ret = BOARD_SIZE - 1 - p;
        assert(ret >= 0);
        return ret;
    }

    Board();

    void init(const std::string& fen = INIT_POSITION_FEN);

    byte castleRights() {
        return _castleRights;
    }

    void setCastleRights(byte cr) {
        _castleRights = cr;
    }

    bool castleAllowed(byte f) const {
        return (f & _castleRights) != 0;
    }

    void revokeCastleRights(byte f) {
        if (f & _castleRights)
            _castleRights ^= f;
    }

    int state(int i) const {
        assert(i < BOARD_SIZE);
        return INIT_STATE[i];
    }

    Piece*& operator [](int i) {
        assert((size_t)i < _board.size());
        return _board[i];
    }

    Piece* getKing(Color clr) {
        return _kings[clr];
    }

    PieceList& getPieceList(Color clr) {
        return (clr == LITE)? _litePieces : _darkPieces;
    }

    int epSq() {
        return _epSq;
    }

    void setEpSq(int ep) {
        _epSq = ep;
    }

    void  print() const;
    std::string getFen() const;

    Piece* getPiece(Color c, Rank r, int p);
    bool  isUnderAttack(int, Color);

private:

    MAKE_NONCOPYABLE(Board);

    byte         _castleRights;
    int          _epSq;

    PieceBoard   _board;

    PieceList    _litePieces;
    PieceList    _darkPieces;

    Piece*       _kings[2];  // references to kings of both sides
};

#endif // BOARD_HPP
