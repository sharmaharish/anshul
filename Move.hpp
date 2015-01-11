#ifndef MOVE_HPP
#define MOVE_HPP

#include <string>

#include "common.hpp"
#include "constants.hpp"

class Piece;

/**
 * Move structure
 */
struct Move
{
    Move();
    Move(int f, int to, MoveType type, Piece* cp);
    Move(int f, int to, MoveType type = NORMAL_MOVE);

    bool operator ==(const Move& m)
    {
        return _from == m._from && _to == m._to && _type == m._type;
    }

    std::string toAlgebric();

    static std::string toAlgebric(int from, int to);
    static bool isAlgebric(const std::string& m);

    static Move toMove(const char* str);
    static Move toMove(const std::string& str);

    int      _from;
    int      _to;
    int      _epSq;
    int      _score;
    MoveType _type;
    byte     _castleRights;
    Piece*   _capture;
};

#endif // MOVE_HPP
