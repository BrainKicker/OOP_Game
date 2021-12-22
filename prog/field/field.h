#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include <functional>
#include <memory>

#include "../../lib/containers/vector/Vector.h"
#include "../../lib/containers/matrix/Matrix.h"
#include "../../lib/containers/queue/Queue.h"
#include "../../lib/utils/type_utils.h"

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
    friend class sfml_adapter;

    using field_changer = std::function<void(field&)>;

    enum cell_defining_sumbols {
        CELL_GROUND_SYMBOL = ' ',
        CELL_WALL_SYMBOL = '#'
    };

    struct field_template {
        int m_id;
        int m_width, m_height;
        geo::i_point m_entry, m_exit;
        Vector<const char*> m_cells;
        field_changer enemies_generator, artifacts_generator;
    };

    static const Vector<field_template> field_templates;

    static const int distance_unvisited = INT32_MAX; // must be big!!!

private:

    inline static const char *const UNKNOWN_SIGNAL_ERROR = "Unknown signal error.";
    inline static const char *const UNKNOWN_CELL_SYMBOL  = "Unknown cell symbol.";

    std::shared_ptr<Logger> m_logger;

    int m_id;
    int m_width, m_height;
    geo::i_point m_entry, m_exit;
    Matrix<cell*> m_cells;
    Matrix<int> m_distances, m_distances_throw_enemies;

    player* m_player;
    Vector<enemy*> m_enemies;
    Vector<artifact*> m_artifacts;

    bool m_instant_step_on_action = true;

    game_condition m_game_condition = game_condition::RUNNING;

    Vector<geo::i_point> get_neighbors(geo::i_point coords) const;

    void evaluate_distances();

    void move_character(character* c, geo::i_point coords);

    void handle_character_action(character* c, action act);

    void players_turn();
    void enemies_turn();

    void check_if_character_dead(character* c);

    void load();
    void reload();
    void clear();

    void apply_logger();

public:

    field(int id, std::shared_ptr<Logger> logger = nullptr);

    ~field();

    void send_sygnal(sygnal signal);

    int width() const;
    int height() const;

    cell::cell_type get_cell_type(int x, int y) const;

    const player& get_player() const;
    const Vector<enemy*> get_enemies() const;
    const Vector<artifact*> get_artifacts() const;

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

    std::shared_ptr<Logger> get_logger();
    void set_logger(std::shared_ptr<Logger> logger);

    void step();
};

#endif //GAME_FIELD_H