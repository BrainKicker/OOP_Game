#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include "../geometry/geo.h"
#include "../../lib/utils/logger/Observable.h"

class entity : public Observable {
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

    geo::i_point m_coords;

    entity(geo::i_point coords = { -1, -1 });

    void print(std::ostream &out) const override;

public:

    ~entity() override = default;

    const geo::i_point& coords() const;
    void set_coords(geo::i_point coords);
};

#endif //GAME_ENTITY_H