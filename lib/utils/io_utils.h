#ifndef GAME_IO_UTILS_H
#define GAME_IO_UTILS_H

#include <iostream>
#include <stdarg.h>

class io_utils {
public:
    static void read(std::istream& in, int count, ...) {
        va_list vl;
        va_start(vl, count);

    }
};

#endif //GAME_IO_UTILS_H