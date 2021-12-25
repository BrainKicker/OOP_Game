#include "player.h"

void player::print(std::ostream& out) const {
    out << "player{ coords=" << coords() << ", max_hp=" << max_hp() << ", hp=" << hp() << ", damage=" << damage() << ", is_melee=" << melee() << ", is_alive=" << alive() << ", artifacts=" << m_artifacts << " }";
}

player::player(geo::i_point coords) : character(coords) {}

direction player::dir() {
    return m_dir;
}

void player::set_dir(direction dir) {
    m_dir = dir;
}

void player::save(std::ostream& out) const {
    character::save(out);
    out << (int) m_dir << '\n';
}

void player::load(std::istream& in) {
    character::load(in);
    int dir;
    in >> dir;
    if (in.fail())
        throw load_error{};
    m_dir = (direction) dir;
}