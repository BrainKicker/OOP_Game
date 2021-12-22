#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H

#include <functional>

#include "../character.h"
#include "../../../field/action.h"

class field; // pre-declaration

class enemy : public character {

public:

    using strategy = std::function<action(const enemy&, const field&)>;

    enum enemy_type {
        ZOMBIE = 0,
        SKELETON
    };

    struct enemy_info {
        enemy_type m_type;
        int m_max_hp;
        int m_hp;
        int m_damage;
        bool m_melee;
        strategy m_strategy;
    };

    static const Vector<enemy_info> enemy_infos;

private:

    static const strategy default_melee_strategy;

    enemy_type m_type;

protected:

    void print(std::ostream &out) const override;

public:

    enemy(enemy_type type, geo::i_point coords = { -1, -1 });

    enemy_type type() const;

    action get_action(const field& f);
};

#endif //GAME_ENEMY_H