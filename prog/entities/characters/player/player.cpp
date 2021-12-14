#include "player.h"

player::player(geo::i_point coords) : character(PLAYER, coords) {}

direction player::dir() {
    return m_dir;
}

void player::set_dir(direction dir) {
    m_dir = dir;
}