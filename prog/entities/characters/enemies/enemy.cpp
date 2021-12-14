#include "enemy.h"

#include "../../../field/field.h"

const enemy::strategy enemy::default_melee_strategy = [](const enemy& en, const field& f) -> action {
    return action(action::TRY_TO_MOVE_ELSE_ATTACK, f.m_directions[en.m_coords.first][en.m_coords.second]);
};

const vector<enemy::enemy_info> enemy::enemy_infos = {
        {
            ZOMBIE,
            90,
            90,
            20,
            true,
            default_melee_strategy
        },
        {
            SKELETON,
            50,
            50,
            10,
            true,
            default_melee_strategy
        }
};

enemy::enemy(enemy::enemy_type type, geo::i_point coords) : character(ENEMY, coords) {
    m_type = type;
    m_max_hp = enemy_infos[m_type].m_max_hp;
    m_hp = enemy_infos[m_type].m_hp;
    m_damage = enemy_infos[m_type].m_damage;
    m_melee = enemy_infos[m_type].m_melee;
}

action enemy::get_action(const field& f) {
    return enemy_infos[m_type].m_strategy(*this, f);
}