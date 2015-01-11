#include "Move.hpp"
#include "Piece.hpp"
#include "Board.hpp"

using namespace std;

/**
 */
Move::Move()
    : _from(0)
    , _to(0)
    , _epSq(0)
    , _score(0)
    , _type(NORMAL_MOVE)
    , _castleRights(0)
{
}

/**
 */
Move::Move(int fr, int to, MoveType type)
    : _from(fr)
    , _to(to)
    , _epSq(0)
    , _score(0)
    , _type(type)
    , _castleRights(0)
{
}

/**
 */
Move::Move(int fr, int to, MoveType type, Piece* cp)
    : _from(fr)
    , _to(to)
    , _epSq(0)
    , _score(0)
    , _type(type)
    , _castleRights(0)
    , _capture(cp)
{
}

/**
 */
string Move::toAlgebric(int from, int to)
{
    string str(4, '0');

    str[0] = from % 10 + 96;
    str[1] = 58 - from / 10;
    str[2] = to % 10 + 96;
    str[3] = 58 - to / 10;

    return str;
}

/**
 */
string Move::toAlgebric()
{
    return toAlgebric(_from, _to);
}

/**
 */
Move Move::toMove(const char* str)
{
    int from = Board::alg2ord(str);
    int to   = Board::alg2ord(str + 2);

    return Move(from, to);
}

/**
 */
Move Move::toMove(const string& str)
{
    return toMove(str.c_str());
}

/**
 */
bool Move::isAlgebric(const string& m)
{
    return (m.size() == 4) &&
        (tolower(m[0]) >= 'a' && tolower(m[0]) <= 'h') &&
        (tolower(m[1]) >= '1' && tolower(m[1]) <= '8') &&
        (tolower(m[2]) >= 'a' && tolower(m[2]) <= 'h') &&
        (tolower(m[3]) >= '1' && tolower(m[3]) <= '8');
}
