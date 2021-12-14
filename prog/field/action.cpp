#include "action.h"

action::action(action::action_type type, direction dir, bool friendly_fire)
: m_type(type), m_by_dir(true), m_dir(dir), m_friendly_fire(friendly_fire) {}

action::action(action::action_type type, geo::i_point coords, bool friendly_fire)
: m_type(type), m_by_dir(false), m_coords(coords), m_friendly_fire(friendly_fire) {}