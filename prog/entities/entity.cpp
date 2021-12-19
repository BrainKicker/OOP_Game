#include "entity.h"

entity::entity(entity_type type, geo::i_point coords) : m_type(type), m_coords(coords) {}

entity::entity_type entity::get_entity_type() const {
    return m_type;
}

const geo::i_point& entity::coords() const {
    return m_coords;
}

void entity::set_coords(geo::i_point coords) {
    m_coords = coords;
}