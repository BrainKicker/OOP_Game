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

void entity::save(std::ostream& out) const {
    out << m_coords.first << ' ' << m_coords.second << '\n';
}

void entity::load(std::istream& in) {
    in >> m_coords.first;
    if (in.fail())
        throw load_error{};
    in >> m_coords.second;
    if (in.fail())
        throw load_error{};
}