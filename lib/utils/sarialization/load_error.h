#ifndef GAME_LOAD_ERROR_H
#define GAME_LOAD_ERROR_H

class load_error : public std::runtime_error {
public:
    load_error() : std::runtime_error("load error") {}
};

#endif //GAME_LOAD_ERROR_H