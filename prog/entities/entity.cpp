#include "entity.h"

entity::entity(geo::i_point coords) : m_coords(coords) {
    notify();
}

void entity::print(std::ostream& out) const {
    out << "entity{ coords=" << coords() << " }";
}

const geo::i_point& entity::coords() const {
    return m_coords;
}

void entity::set_coords(geo::i_point coords) {
    m_coords = coords;
    notify();
}