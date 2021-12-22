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