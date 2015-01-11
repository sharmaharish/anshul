#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <csignal>
#include <fstream>
#include <iostream>

#include "Config.hpp"
#include "Engine.hpp"
#include "Log.hpp"
#include "Piece.hpp"
#include "util.hpp"

using namespace std;

/**
 * Constructor
 */
Engine::Engine()
    : _self(DARK)
    , _turn(LITE)
    , _rival(DARK)
{
    srand((uint32_t)time(0));
}

/**
 * Starts the engine
 */
void Engine::play()
{
    string next;
    Move m;

    _board.print();
    while (true) {
        if (_turn == _self) {
            if (getBookMove(m))
                makeMove(m);
            else if (think()) {
                cout << "Best move: " << _bestMove.toAlgebric();
                makeMove(_bestMove);
            }
            else
                assert("Failed to find a valid move" && false);
        }
        else {
            cout << "\nEnter Move "<< ((_turn == LITE) ? "[WHITE]: "
                                       : "[BLACK]: ");
            cin >> next;
            if (next == "q"|| next == "quit" || next == "x" || next == "exit") {
                cout << "bye";
                exit(0);
            }

            if (next == "h" || next == "help") {
                // todo
                continue;
            }

            if (!Move::isAlgebric(next)) {
                cout << "\tINVALID MOVE. Try again.";
                continue;
            }

            m = Move::toMove(next);
            setType(m);

            if (!validateMove(m)) {
                cout << "\tINVALID MOVE. Try again.";
                continue;
            }

            if (!makeMove(m))
                continue;
        }

        _board.print();
    }
}

/**
 * xboard protocol
 */
void Engine::xboard()
{
    cout.setf(ios_base::unitbuf);
    cin.setf(ios_base::unitbuf);

    Move m;
    string command;

    signal(SIGINT, SIG_IGN);

    while (true) {
        if (_turn == _self) {
            if (getBookMove(m))
                makeMove(m);
            else if (think())
                makeMove(_bestMove);
            else {
                LOG("anshul: failed to find a move !");
                LOG("anshul: position[" << _board.getFen() << "]");
                LOG("anshul: moves[" << getPlayedMoves() << "]");
                return;
            }

            LOG("anshul: " << m.toAlgebric());;
            cout << "move " + m.toAlgebric() + "\n";
        }

        cin >> command;
        command = trim(command);

        LOG("xboard: " << command);

        if (command.empty())
            return;

        if (command == "xboard")
            continue;

        if (command == "new") {
            _board.init();
            _self = DARK;
            _turn = LITE;
            _rival = DARK;
            continue;
        }
        if (command == "quit")
            return;
        if (command == "force") {
            // todo
            continue;
        }
        if (command == "white") {
            _rival = _turn = LITE;
            _self = DARK;
            continue;
        }
        if (command == "black") {
            _self = _turn = LITE;
            _rival = DARK;
            continue;
        }
        if (command == "st") {
            // todo
            continue;
        }
        if (command == "sd") {
            // todo
            continue;
        }
        if (command == "time") {
            // todo
            continue;
        }
        if (command == "otim") {
            // todo
            continue;
        }
        if (command == "go") {
            // todo
            continue;
        }
        if (command == "hint") {
            // todo
            continue;
        }
        if (command == "undo") {
            unmakeMove();
            unmakeMove();
            continue;
        }
        if (command == "remove") {
            unmakeMove();
            unmakeMove();
            continue;
        }
        if (command == "post") {
            // todo
            continue;
        }
        if (command == "nopost") {
            // todo
            continue;
        }

        if (!Move::isAlgebric(command)) {
            LOG("anshul: Error (invalid move - non algebric notation): " << command);
            continue;
        }

        m = Move::toMove(command);
        setType(m);

        if (!validateMove(m)) {
            LOG("anshul: Error (invalid move - validation failed): " << command);
            continue;
        }

        if (!makeMove(m)) {
            LOG("anshul: Error (invalid move - failed to make move): " << command);
            continue;
        }
    }
}

/**
 * Validate the given move
 * @return boolean
 */
bool Engine::validateMove(const Move& m)
{
    if (!_board[m._from])
        return false;
    if (_turn != _board[m._from]->color())
        return false;
    if (_board[m._from]->isMoveValid(m) == false)
        return false;

    Piece* king = _board.getKing(_turn);
    if (king == _board[m._from])
        return !_board.isUnderAttack(m._to, _rival);

    return true;
}

/**
 * Gets the next book move according to game position
 */
bool Engine::getBookMove(Move& m)
{
    static bool trybook = true;

    if (!trybook)
        return false;

    string moves = getPlayedMoves();

    _book.open("anshul.book");

    bool found = false;
    vector<string> bookmoves;

    while (_book) {
        char buf[120] = { 0 };
        _book.getline(buf, 120 - 1);

        found = (buf == strstr(buf, moves.c_str()));
        if (found)
            bookmoves.push_back(buf);
        if (bookmoves.empty() == false && !found)
            break;
    }

    _book.close();

    if (bookmoves.empty())
        return trybook = false;

    // randomly select one of the available opening lines
    int ind = rand() % bookmoves.size();
    // get the next move from the book
    moves.assign(bookmoves[ind], moves.size(), 4);
    // convert the algebric move to Move object
    m = Move::toMove(moves);
    setType(m);

    return true;
}

/**
 * Retrieves the list of moves played till a point in the game
 */
string Engine::getPlayedMoves()
{
    string mlist = "";
    MoveList::iterator it = _movesPlayed.begin();
    MoveList::iterator end = _movesPlayed.end();
    for (; it != end; ++it) {
        mlist += (*it).toAlgebric();
    }
    return mlist;
}

/**
 * Sets the move type in Move object
 */
void Engine::setType(Move& m)
{
    const Piece& p = *_board[m._from];
    switch (p.rank())
    {
        case PAWN: {
            const int cdiff = abs(Board::col(m._from) - Board::col(m._to));
            if (cdiff > 0) {
                m._type = _board[m._to]? CAPTURE_MOVE : ENPASSE_MOVE;
                break;
            }

            const int rdiff = abs(Board::row(m._from) - Board::row(m._to));
            if (rdiff == 2)
                m._type = PAWN_DOUBLE_MOVE;
            else if (rdiff == 1) {
                const int trow = Board::row(m._to);
                if ((_turn == DARK && trow == 1) ||
                    (_turn == LITE && trow == 8))
                    m._type = PROMOTE_MOVE;
            }

            break;
        }
        case KING:
            if (_turn == DARK) {
                if ((m._from == E8 && m._to == G8) ||
                    (m._from == E8 && m._to == C8))
                    m._type = CASTLE_MOVE;
            }
            else {
                if ((m._from == E1 && m._to == G1) ||
                    (m._from == E1 && m._to == C1))
                    m._type = CASTLE_MOVE;
            }

            break;
        case KNIGHT:
        case ROOK:
        case BISHOP:
        case QUEEN:
            break;
    }
}

/**
 * Perform the move on the board
 */
bool Engine::makeMove(Move& m)
{
    m._epSq = _board.epSq();
    m._castleRights = _board.castleRights();

    switch (m._type) {
        case CASTLE_MOVE:
            _board[m._from]->moveTo(m._to);
            if (_turn == LITE) {
                if (m._to == G1)
                    _board[H1]->moveTo(F1);
                if (m._to == C1)
                    _board[A1]->moveTo(D1);
            }
            else {
                if (m._to == G8)
                    _board[H8]->moveTo(F8);
                if (m._to == C8)
                    _board[A8]->moveTo(D8);
            }
            _board.setEpSq(0);
            break;
        case PROMOTE_MOVE:
            _board[m._to] = _board.getPiece(_turn, QUEEN, m._to);
            _board[m._from]->setLive(false);
            _board[m._from] = 0;
            _board.setEpSq(0);
            break;
        case ENPASSE_MOVE: {
            _board[m._from]->moveTo(m._to);
            const int ep_cap = m._to + ((_turn == LITE)? 10 : -10);
            m._capture = _board[ep_cap];
            m._capture->setLive(false);
            _board[ep_cap] = 0;
            _board.setEpSq(0);
            break;
        }
        case PAWN_DOUBLE_MOVE:
            _board[m._from]->moveTo(m._to);
            _board.setEpSq((m._to + m._from) / 2);
            break;
        case NORMAL_MOVE:
        case CAPTURE_MOVE:
            if (!_board[m._from] || (_board[m._from]->color() != _turn) ||
                ((m._type == CAPTURE_MOVE) && (!_board[m._to] ||
                                               (_board[m._to]->color() != _rival))))
            {
                printDiagnosticInfo();
                LOG("Current move : " << m.toAlgebric());
                assert(false);
            }
            m._capture = _board[m._from]->moveTo(m._to);
            _board.setEpSq(0);
            break;
        default:
            assert("Invalid move type !!" && false);
    }

    swap(_turn, _rival);
    _movesPlayed.push_back(m);

    Piece* king = _board.getKing(_rival);
    if (king->isUnderAttack()) {
        unmakeMove();
        return false;
    }

    return true;
}

/**
 * Undo the last move on the board
 */
void Engine::unmakeMove()
{
    Move m = _movesPlayed.back();
    _movesPlayed.pop_back();
    swap(_turn, _rival);

    switch (m._type) {
        case CASTLE_MOVE:
            _board[m._to]->moveTo(m._from);
            if (_turn == LITE) {
                if (m._to == G1)
                    _board[F1]->moveTo(H1);
                if (m._to == C1)
                    _board[D1]->moveTo(A1);
            }
            else {
                if (m._to == G8)
                    _board[F8]->moveTo(H8);
                if (m._to == C8)
                    _board[D8]->moveTo(A8);
            }
            break;
        case PROMOTE_MOVE:
            _board[m._to]->setLive(false);
            _board[m._to] = 0;
            _board[m._from] = _board.getPiece(_turn, PAWN, m._from);
            break;
        case ENPASSE_MOVE: {
            const int ep_cap = m._to + ((_turn == LITE)? 10 : -10);
            _board[m._to]->moveTo(m._from);
            _board[ep_cap] = m._capture;
            m._capture->setLive(true);
            m._capture->setPlace(ep_cap);
            break;
        }
        case PAWN_DOUBLE_MOVE:
            _board[m._to]->moveTo(m._from);
            break;
        case NORMAL_MOVE:
        case CAPTURE_MOVE:
            _board[m._to]->moveTo(m._from);
            if (m._capture) {
                _board[m._to] = m._capture;
                m._capture->setLive(true);
                m._capture->setPlace(m._to);
            }
            break;
    }

    _board.setEpSq(m._epSq);
    _board.setCastleRights(m._castleRights);
}

/**
 * Generate moves for current ply
 */
bool Engine::genMoves(MoveList& moves)
{
    Piece* king = _board.getKing(_turn);
    if (king->isUnderAttack()) {
        king->genCaptureMoves(moves);
        king->genMoves(moves);
        return !moves.empty();
    }

    PieceList& pl = _board.getPieceList(_turn);
    PieceList::iterator it = pl.begin();
    PieceList::iterator end = pl.end();
    for (; it != end; ++it) {
        Piece* p = *it;
        if (p && p->live())
            p->genCaptureMoves(moves);
    }

    for (it = pl.begin(); it != end; ++it) {
        Piece* p = *it;
        if (p && p->live())
            p->genMoves(moves);
    }

    return !moves.empty();
}

/**
 * Think to generate next move for computer side. Uses iterative deepening and
 * alpha beta search to converge to the best move.
 */
bool Engine::think()
{
    int depth = 1;
    int max_depth = Config::instance().maxDepth();

    while (depth <= max_depth) {
        search(1, depth, -INFINITY, INFINITY);
        depth++;
    }

    return true;
}

/**
 * Search the best move using alpha beta pruning.
 */
int Engine::search(int ply, int depth, int alpha, int beta)
{
    if (depth <= 0)
        return evaluate();

    MoveList moves;
    if (!genMoves(moves))
        return evaluate();

    int score = -INFINITY;
    MoveList::iterator it  = moves.begin();
    MoveList::iterator end = moves.end();

    for (; it != end; ++it) {
        if (makeMove(*it)) {
            score = -search(ply + 1, depth - 1, -beta, -alpha);
            unmakeMove();
            if (score > alpha) {
                alpha = score;
                if (ply == 1)
                    _bestMove = *it;
            }
            if (score >= beta) {
                return beta;
                if (ply == 1)
                    _bestMove = *it;
            }
        }
    }

    return alpha;
}

/**
 * Evaluate the board position
 */
int Engine::evaluate()
{
    int mat_value = 0;    // material value
    int plc_value = 0;    // place value
    int pos_value = 0;    // position value

    int pawn_count[2][8] = { { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 } };
    int pawn_postn[2][8] = { { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 } };

    for (int i = BOARD_START; i < BOARD_END; ++i) {
        Piece* p = _board[i];
        if (!p) continue;
        mat_value += (p->color() == _turn)? p->value() : -p->value();
        plc_value += (p->color() == _turn)? p->placeValue() : -p->placeValue();
        switch (p->rank()) {
            case PAWN: {
                // forward pawn bonus
                // doubled pawn penalty
                const int r = Board::row(i);
                const int c = Board::col(i);

                if (p->color() == LITE) {
                    pawn_count[LITE][c - 1]++;
                    if (pawn_postn[LITE][c - 1] < r)
                        pawn_postn[LITE][c - 1] = r;
                }
                else {
                    pawn_count[DARK][c - 1]++;
                    // TODO
                }

                break;
            }
            case ROOK:
                // TODO
                // doubled rook bonus
                // open file bonus
                // single rook penalty
                break;
            case KNIGHT:
                // TODO
                break;
            case BISHOP:
                // TODO
                // double bishop bonus
                // single bishop penalty
                break;
            case QUEEN:
                // TODO
                break;
            case KING:
                // TODO
                // castled king bonus
                // open king file penalty
                // lost castling rights penaltly
                break;
            default:
                assert("Invalid piece type !!" && false);
                break;
        }
    }

    return mat_value + plc_value + pos_value;
}

/**
 */
void Engine::printDiagnosticInfo()
{
    _board.print();
    LOG("Moves played : " << getPlayedMoves());
}
