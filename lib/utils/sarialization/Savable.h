#ifndef GAME_SAVABLE_H
#define GAME_SAVABLE_H

#include <iostream>

#include "load_error.h"

class Savable {
public:
    virtual ~Savable() = default;
    virtual void save(std::ostream& out) const = 0;
    virtual void load(std::istream& in) = 0;
};

#endif //GAME_SAVABLE_H