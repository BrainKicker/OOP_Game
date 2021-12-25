#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "../character.h"
#include "../../../field/direction.h"

class player : public character {

    direction m_dir = direction::NONE;

protected:

    void print(std::ostream &out) const override;

public:

    player(geo::i_point coords = { -1, -1 });

    direction dir();
    void set_dir(direction dir);

    void save(std::ostream &out) const override;
    void load(std::istream &in) override;
};

#endif //GAME_PLAYER_H