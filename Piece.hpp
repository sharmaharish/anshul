#ifndef PIECE_HPP
#define PIECE_HPP

#include <string>

#include "Board.hpp"
#include "types.hpp"

class Board;

/**
 * Piece
 */
class Piece
{
public:

    Piece(Color clr, Rank rnk, int value, int place, cstr symbol, bool slide, Board&);
    virtual ~Piece() {}

    Color color()   const { return _color; }
    Rank  rank()    const { return _rank; }
    int   place()   const { return _place; }
    int   col()     const { return Board::col(_place); }
    int   row()     const { return Board::row(_place); }
    int   value()   const { return _value; }
    bool  live()    const { return _live; }
    bool  notLive() const { return !_live; }

    int   placeValue() const {
        assert((size_t)_place < _values.size());
        return _values[_place];
    }

    const std::string& symbol() const { return _symbol; }

    void setLive(bool stat) { _live = stat; }

    virtual bool isMoveValid(const Move&);
    virtual bool isUnderAttack();

    virtual void genMoves(MoveList&);
    virtual void genCaptureMoves(MoveList&);

    virtual void setPlace(int p) { _place = p; }

    virtual Piece* moveTo(int to);

protected:

    Color       _color;
    Rank        _rank;
    bool        _slide;
    bool        _live;
    int         _place;
    int         _value;
    Board&      _board;
    std::string _symbol;

    PlaceValues _values;
    Offsets     _offsets; // move offsets for this piece
};

#endif // _PIECE_HPP
