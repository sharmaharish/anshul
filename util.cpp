#include "util.hpp"

/**
 */
std::string trim(const std::string& line)
{
    size_t start = line.find_first_not_of(" \t\n\r");
    size_t end = line.find_last_not_of(" \t\n\r");

    if (start != std::string::npos && end != std::string::npos)
        return line.substr(start, end - start + 1);

    return line;
}
