#include <iostream>

#include "Engine.hpp"

using namespace std;

/**
 * usage of the engine
 */
static void usage()
{
    cout << "\nanshul [options]";
    cout << "\n\toptions: -h";
}

/**
 * main method
 */
int main(int argc, char *argv[])
{
    if (argc > 1 && !strcmp(argv[1], "-h") ) {
        usage();
        return 0;
    }

    bool xboard = true;
    for (int i = 0; i < argc; ++i) {
        if (!strcmp(argv[i], "--console")) {
            xboard = false;
            break;
        }
    }

    Engine anshul;
    if (xboard)
        anshul.xboard();
    else
        anshul.play();

    return 0;
}

