#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include <functional>
#include <memory>

#include "../../lib/containers/vector/vector.h"
#include "../../lib/containers/matrix/matrix.h"
#include "../../lib/containers/queue/queue.h"

#include "../entities/characters/player/player.h"
#include "../entities/characters/enemies/enemy.h"
#include "../entities/artifacts/artifact.h"
#include "cell/cell.h"

#include "../geometry/geo.h"

enum class sygnal {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STEP,
    RESTART
};

enum class game_condition {
    RUNNING,
    WIN,
    LOSE
};

class field {
public:

    friend class enemy;

    using field_changer = std::function<void(field&)>;

    enum cell_defining_sumbols {
        CELL_GROUND_SYMBOL = ' ',
        CELL_WALL_SYMBOL = '#'
    };

    struct field_template {
        int m_id;
        int m_width, m_height;
        geo::i_point m_entry, m_exit;
        vector<const char*> m_cells;
        field_changer enemies_generator, artifacts_generator;
    };

    static const vector<field_template> field_templates;

private:

    inline static const char *const UNKNOWN_SIGNAL_ERROR = "Unknown signal error.";
    inline static const char *const UNKNOWN_CELL_SYMBOL  = "Unknown cell symbol.";

    int m_id;
    int m_width, m_height;
    geo::i_point m_entry, m_exit;
    matrix<cell*> m_cells;
    matrix<direction> m_directions;

    player* m_player;
    vector<enemy*> m_enemies;
    vector<artifact*> m_artifacts;

    bool m_instant_step_on_action = true;

    game_condition m_game_condition = game_condition::RUNNING;

    void mark_directions();

    void move_character(character* c, geo::i_point coords);

    void handle_character_action(character* c, action act);

    void players_turn();
    void enemies_turn();

    void check_if_character_dead(character* c);

    void load();
    void reload();
    void clear();

public:

    explicit field(int id);

    ~field();

    void send_sygnal(sygnal signal);

    int width();
    int height();

    cell::cell_type get_cell_type(int x, int y) const;

    const player& get_player() const;
    const vector<enemy*> get_enemies() const;
    const vector<artifact*> get_artifacts() const;

    geo::i_point get_entry_coords() const;
    geo::i_point get_exit_coords() const;

    game_condition get_game_condition() const;

    void add_enemy(enemy* en);
    void add_artifact(artifact* art);

    [[nodiscard]] enemy* remove_enemy(int index);
    void delete_enemy(int index);
    [[nodiscard]] artifact* remove_artifact(int index);
    void delete_artifact(int index);

    [[nodiscard]] enemy* remove_enemy(enemy* ptr);
    void delete_enemy(enemy* ptr);
    [[nodiscard]] artifact* remove_artifact(artifact* ptr);
    void delete_artifact(artifact* ptr);

    void step();
};

#endif //GAME_FIELD_H