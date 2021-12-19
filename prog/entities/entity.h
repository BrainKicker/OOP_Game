#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include "../geometry/geo.h"

class entity {
public:

    enum entity_type {
        NONE,
        ENTITY,
        ARTIFACT,
        CHARACTER,
        PLAYER,
        ENEMY
    };

protected:

    entity_type m_type;
    geo::i_point m_coords;

    entity(entity_type type, geo::i_point coords = { -1, -1 });

public:

    entity_type get_entity_type() const;

    const geo::i_point& coords() const;
    void set_coords(geo::i_point coords);
};

#endif //GAME_ENTITY_H