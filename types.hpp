#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>
#include <array>

#include "common.hpp"
#include "Move.hpp"

class Piece;

typedef std::array<int, BOARD_SIZE> PlaceValues;
typedef std::array<Piece*, BOARD_SIZE> PieceBoard;

typedef std::vector<Piece*> PieceList;
typedef std::vector<Move> MoveList;
typedef std::vector<int> Offsets;

typedef std::pair<int, int> IntPair;

#endif // TYPES_HPP
