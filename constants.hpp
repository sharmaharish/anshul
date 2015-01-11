#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

/**
 * Piece colors
 */
enum Color
{
    LITE,
    DARK
};

/**
 * Piece ranks
 */
enum Rank
{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

/**
 * Board squares
 */
enum Square
{
    A8 = 21, B8, C8, D8, E8, F8, G8, H8,
    A7 = 31, B7, C7, D7, E7, F7, G7, H7,
    A6 = 41, B6, C6, D6, E6, F6, G6, H6,
    A5 = 51, B5, C5, D5, E5, F5, G5, H5,
    A4 = 61, B4, C4, D4, E4, F4, G4, H4,
    A3 = 71, B3, C3, D3, E3, F3, G3, H3,
    A2 = 81, B2, C2, D2, E2, F2, G2, H2,
    A1 = 91, B1, C1, D1, E1, F1, G1, H1
};

/**
 * Files on board
 */
enum File
{
    A_FILE,
    B_FILE,
    C_FILE,
    D_FILE,
    E_FILE,
    F_FILE,
    G_FILE,
    H_FILE
};

/**
 * Castling rights for a side
 */
enum CastleRights
{
    LITE_KING_SIDE  = 0x01,
    DARK_KING_SIDE  = 0x02,
    LITE_QUEEN_SIDE = 0x04,
    DARK_QUEEN_SIDE = 0x08,
    INITIAL_RIGHTS  = (LITE_KING_SIDE | DARK_KING_SIDE | LITE_QUEEN_SIDE | DARK_QUEEN_SIDE)
};

/**
 * Move types
 */
enum MoveType
{
    NORMAL_MOVE,
    CAPTURE_MOVE,
    CASTLE_MOVE,
    PROMOTE_MOVE,
    ENPASSE_MOVE,
    PAWN_DOUBLE_MOVE
};

/**
 * Constants
 */
const int BOARD_SIZE = 120;
const int BOARD_START = 21;
const int BOARD_END = 99;
const int FORWARD_PAWN_BONUS = 20;
const int ISOLATED_PAWN_PENALTY = 20;
const int BACKWARD_PAWN_PENALTY = FORWARD_PAWN_BONUS;

const int CASTLED_KING_BONUS = 50;
const int EXPOSED_KING_PENALTY = CASTLED_KING_BONUS;

const int ROOK_ON_SEMI_OPEN_FILE_BONUS = 10;
const int ROOK_ON_OPEN_FILE_BONUS = 15;
const int ROOK_ON_7TH_BONUS = 20;

const int HANGING_PIECE_PENALTY = 20;

const int INIT_STATE[] = { 0,0,0,0,0,0,0,0,0,0,
                           0,0,0,0,0,0,0,0,0,0,
                           0,1,1,1,1,1,1,1,1,0,
                           0,1,1,1,1,1,1,1,1,0,
                           0,1,1,1,1,1,1,1,1,0,
                           0,1,1,1,1,1,1,1,1,0,
                           0,1,1,1,1,1,1,1,1,0,
                           0,1,1,1,1,1,1,1,1,0,
                           0,1,1,1,1,1,1,1,1,0,
                           0,1,1,1,1,1,1,1,1,0,
                           0,0,0,0,0,0,0,0,0,0,
                           0,0,0,0,0,0,0,0,0,0 };

#endif // CONSTANTS_HPP
