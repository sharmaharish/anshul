#include "Log.hpp"

/**
 */
Log::Log()
    : _log("anshul.log")
{
}

/**
 */
Log::~Log()
{
    _log.close();
}
