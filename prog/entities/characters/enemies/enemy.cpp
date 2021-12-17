#include "enemy.h"

#include "../../../field/field.h"
#include "../../../../lib/algorithm/sorts/heapsort.h"

const enemy::strategy enemy::default_melee_strategy = [](const enemy& en, const field& f) -> action {

    class comp {
        const enemy& m_en;
        const field& m_field;
        const matrix<int>& m_distances;
    public:
        comp(const enemy& en, const field& f, const matrix<int>& distances) : m_en(en), m_field(f), m_distances(distances) {}
        bool operator()(const geo::i_point& p1, const geo::i_point& p2) {
            int dist_diff = m_distances[p1.first][p1.second] - m_distances[p2.first][p2.second];
            if (dist_diff != 0)
                return dist_diff < 0;
            const auto& player_coords = m_field.get_player().coords();
            const int player_enemy_coords_diff =
                    std::abs(player_coords.first - m_en.coords().first) - abs(player_coords.second - m_en.coords().second);
            if (player_enemy_coords_diff < 0 /* x < y */) {
                return std::abs(player_coords.first - p1.first) < std::abs(player_coords.first - p2.first);
            } else if (player_enemy_coords_diff > 0 /* x > y */) {
                return std::abs(player_coords.first - p1.second) < std::abs(player_coords.first - p2.second);
            } else /* x == y */ {
                return std::rand() < RAND_MAX / 2;
            }
        }
    };

    vector<geo::i_point> neighbors = f.get_neighbors(en.coords());

    for (int i = 0; i < neighbors.size();) {
        if (f.m_distances[neighbors[i].first][neighbors[i].second] == field::distance_unvisited) {
            neighbors.remove(i);
        } else {
            ++i;
        }
    }

    if (neighbors.empty()) {

        neighbors = f.get_neighbors(en.coords());

        for (int i = 0; i < neighbors.size();) {
            if (f.m_distances_throw_enemies[neighbors[i].first][neighbors[i].second] == field::distance_unvisited) {
                neighbors.remove(i);
            } else {
                ++i;
            }
        }

        if (neighbors.empty())
            return action(action::DO_NOTHING, { -1, -1 });

        heapsort(neighbors.begin(), neighbors.end(), comp(en, f, f.m_distances_throw_enemies));
    } else {
        heapsort(neighbors.begin(), neighbors.end(), comp(en, f, f.m_distances));
    }

    return action(action::TRY_TO_MOVE_ELSE_ATTACK, neighbors[0]);
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

enemy::enemy_type enemy::type() const {
    return m_type;
}

action enemy::get_action(const field& f) {
    return enemy_infos[m_type].m_strategy(*this, f);
}