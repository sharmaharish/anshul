#ifndef LOG_HPP
#define LOG_HPP

#include <fstream>
#include "common.hpp"

#define LOG(msg) Log::instance() << msg << endl

/**
 */
class Log
{
public:

    ~Log();

    static std::ofstream& instance() {
        static Log obj;
        return obj._log;
    }

private:

    Log();

    std::ofstream _log;
};

#endif // LOG_HPP
