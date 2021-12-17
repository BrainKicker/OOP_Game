#ifndef GAME_ACTION_H
#define GAME_ACTION_H

#include "direction.h"
#include "../geometry/geo.h"

class action {

public:

    enum action_type {
        DO_NOTHING,
        MOVE,
        ATTACK,
        TRY_TO_MOVE_ELSE_ATTACK
    };

    action_type m_type;

    bool m_by_dir;
    bool m_friendly_fire;

    union {
        direction m_dir;
        geo::i_point m_coords;
    };

    action(action_type type, direction dir, bool friendly_fire = false);
    action(action_type type, geo::i_point coords, bool friendly_fire = false);
};

#endif //GAME_ACTION_H