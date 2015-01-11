#include <iostream>
#include <fstream>
#include <cstdlib>

#include "Config.hpp"
#include "Log.hpp"
#include "util.hpp"

#define CFG_SEPARATOR    '='
#define CFG_FILE_NAME    "anshul.cfg"

#define CFG_MAX_DEPTH    "max_depth"
#define CFG_MAX_TIME     "max_time"
#define CFG_PAWN_VALUE   "pawn_value"
#define CFG_ROOK_VALUE   "rook_value"
#define CFG_KNIGHT_VALUE "knight_value"
#define CFG_BISHOP_VALUE "bishop_value"
#define CFG_QUEEN_VALUE  "queen_value"

#define DEF_MAX_DEPTH    8
#define DEF_MAX_TIME     60 // in seconds
#define DEF_PAWN_VALUE   100
#define DEF_ROOK_VALUE   500
#define DEF_KNIGHT_VALUE 300
#define DEF_BISHOP_VALUE 350
#define DEF_QUEEN_VALUE  900

using namespace std;

/**
 */
Config::Config()
{
    refresh();
}

/**
 */
Config::~Config()
{
    _table.clear();
}

/**
 */
void Config::init()
{
    _table.clear();
    _table.insert(Table::value_type(CFG_MAX_DEPTH, DEF_MAX_DEPTH));
    _table.insert(Table::value_type(CFG_MAX_TIME, DEF_MAX_TIME));
    _table.insert(Table::value_type(CFG_PAWN_VALUE, DEF_PAWN_VALUE));
    _table.insert(Table::value_type(CFG_ROOK_VALUE, DEF_ROOK_VALUE));
    _table.insert(Table::value_type(CFG_KNIGHT_VALUE, DEF_KNIGHT_VALUE));
    _table.insert(Table::value_type(CFG_BISHOP_VALUE, DEF_BISHOP_VALUE));
    _table.insert(Table::value_type(CFG_QUEEN_VALUE, DEF_QUEEN_VALUE));
}

/**
 */
void Config::refresh()
{
    init();

    ifstream cfgFile;
    cfgFile.open(CFG_FILE_NAME);

    while (cfgFile) {
        char buf[1024] = { 0 };

        cfgFile.getline(buf, 1023);
        string line = trim(buf);

        if (line.empty() || line[0] == '#')
            continue;

        addKeyValue(line);
    }

    cfgFile.close();

    if (_table.empty()) {
        LOG("Configuration error !");
    }
}

/**
 */
void Config::addKeyValue(const string& line)
{
    _table[getKey(line)] = strtol(getValue(line).c_str(), 0, 10);
}

/**
 */
string Config::getKey(const string& line)
{
    size_t i = line.find_first_of(CFG_SEPARATOR);
    if (i == string::npos)
        return string();
    else
        return trim(line.substr(0, i));
}

/**
 */
string Config::getValue(const string& line)
{
    size_t i = line.find_first_of(CFG_SEPARATOR);
    if (i == string::npos)
        return string();
    else
        return trim(line.substr(i + 1));
}

/**
 */
int Config::get(const string& key, int def) const
{
    Table::const_iterator it = _table.find(key);
    return (it != _table.end())? (*it).second : def;
}

#define DEFINE_GETTER(param, def, pname) \
    int Config::param() const            \
    {                                    \
        return get(pname, def);          \
    }                                    \

DEFINE_GETTER(maxDepth, DEF_MAX_DEPTH, CFG_MAX_DEPTH)
DEFINE_GETTER(maxTime, DEF_MAX_TIME, CFG_MAX_TIME)

DEFINE_GETTER(pawnValue, DEF_PAWN_VALUE, CFG_PAWN_VALUE)
DEFINE_GETTER(rookValue, DEF_ROOK_VALUE, CFG_ROOK_VALUE)
DEFINE_GETTER(knightValue, DEF_KNIGHT_VALUE, CFG_KNIGHT_VALUE)
DEFINE_GETTER(bishopValue, DEF_BISHOP_VALUE, CFG_BISHOP_VALUE)
DEFINE_GETTER(queenValue, DEF_QUEEN_VALUE, CFG_QUEEN_VALUE)

