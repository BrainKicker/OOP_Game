#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "../character.h"
#include "../../../field/direction.h"

class player : public character {

    direction m_dir = direction::NONE;

public:

    player(geo::i_point coords = { -1, -1 });

    direction dir();
    void set_dir(direction dir);
};

#endif //GAME_PLAYER_H