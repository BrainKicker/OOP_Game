#include "entity.h"

entity::entity(entity_type type, geo::i_point coords) : m_type(type), m_coords(coords) {}

entity::entity_type entity::type() {
    return m_type;
}

geo::i_point entity::coords() {
    return geo::i_point();
}

const geo::i_point entity::coords() const {
    return geo::i_point();
}

void entity::set_coords(geo::i_point coords) {
    m_coords = coords;
}