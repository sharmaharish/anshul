#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <map>
#include <string>

#include "common.hpp"

/**
 */
class Config
{
public:

    ~Config();

    void init();
    void refresh();

    int maxDepth() const;
    int maxTime() const;

    int pawnValue() const;
    int rookValue() const;
    int knightValue() const;
    int bishopValue() const;
    int queenValue() const;

private:

    Config();

    MAKE_SINGLETON(Config)

    void addKeyValue(const std::string&);
    std::string getKey(const std::string&);
    std::string getValue(const std::string&);

    int get(const std::string& pname, int def) const;

private:

    typedef std::map<std::string, int> Table;

    Table _table;
};

#endif // _CONFIG_HPP_
