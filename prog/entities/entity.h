#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include "../geometry/geo.h"
#include "../../lib/utils/logger/Observable.h"
#include "../../lib/utils/sarialization/Savable.h"

class entity : public Observable, Savable {

protected:

    geo::i_point m_coords;

    entity(geo::i_point coords = { -1, -1 });

    void print(std::ostream &out) const override;

public:

    ~entity() override = default;

    const geo::i_point& coords() const;
    void set_coords(geo::i_point coords);

    void save(std::ostream &out) const override;
    void load(std::istream &in) override;
};

#endif //GAME_ENTITY_H