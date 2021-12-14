#include "field.h"

const vector<field::field_template> field::field_templates = {
        {
            0,
            13, 8,
            { 0, 4 }, { 12, 4 },
            {
                "##  #####  ##",
                "#           #",
                "      #      ",
                "     ###     ",
                "    #   #    ",
                "     # #     ",
                "#           #",
                "##         ##"
            },
            [](field& f) {
                for (enemy* e : {
                    new enemy(enemy::ZOMBIE, { 6, 2 }),
                    new enemy(enemy::ZOMBIE, { 6, 7 })
                    }) {
                    f.add_enemy(e);
                }
            },
            [](field& f) {

            }
        },
        {
            1,
            13, 8,
            { 5, 7 }, { 7, 7 },
            {
                "# # # # # # #",
                " #         # ",
                "#     #     #",
                "     # #     ",
                "    #   #    ",
                "#    # #    #",
                " #    #    # ",
                "# # # # # # #"
            },
            [](field& f) {
                for (enemy* e : {
                        new enemy(enemy::SKELETON, { 3, 2 }),
                        new enemy(enemy::ZOMBIE, { 10, 3 })
                }) {
                    f.add_enemy(e);
                }
            },
            [](field& f) {

            }
        },
        {
            2,
            13, 8,
            { 0, 7 }, { 12, 0 },
            {
                "   #######   ",
                "  ## # # ##  ",
                "    #   #    ",
                " ##   #   ## ",
                "    # # #    ",
                "     ###     ",
                "    #   #    ",
                " ##       ## "
            },
            [](field& f) {
                for (enemy* e : {
                        new enemy(enemy::SKELETON, { 1, 1 }),
                        new enemy(enemy::SKELETON, { 11, 1 }),
                        new enemy(enemy::ZOMBIE, { 12, 7 })
                }) {
                    f.add_enemy(e);
                }
            },
            [](field& f) {

            }
        },
        {
            3,
            10, 10,
            { 0, 0 }, { 9, 9 },
            {
                    "   # # # #",
                    "## ### # #",
                    " # #     #",
                    "   # # ###",
                    "##      # ",
                    "   ### #  ",
                    "  #    ## ",
                    "#   # ##  ",
                    "### #  # #",
                    "    ##    "
            },
            [](field& f) {
                for (enemy* e : {
                        new enemy(enemy::SKELETON, { 6, 0 }),
                        new enemy(enemy::SKELETON, { 3, 9 })
                }) {
                    f.add_enemy(e);
                }
            },
            [](field& f) {

            }
        }
};

void field::mark_directions() {

    queue<geo::i_point> q;
    q.push(m_player->coords());
    for (int x = 0; x < width(); ++x)
        for (int y = 0; y < height(); ++y)
            m_directions[x][y] = direction::UNDEFINED;
    m_directions[m_player->coords().first][m_player->coords().second] = direction::NONE;

    while (!q.empty()) {
        geo::i_point cur = q.pop();
        std::initializer_list<pair<geo::i_point,direction>> neighbors = {
                { { cur.first - 1, cur.second }, direction::RIGHT },
                { { cur.first, cur.second - 1 }, direction::DOWN },
                { { cur.first + 1, cur.second }, direction::LEFT },
                { { cur.first, cur.second + 1 }, direction::UP }
        };
        for (const auto& n : neighbors) {
            if (n.first.first >= 0 && n.first.first < width() && n.first.second >= 0 && n.first.second < height()) {
                if (m_cells[n.first.first][n.first.second]->type() != cell::WALL) {
                    if (m_directions[n.first.first][n.first.second] == direction::UNDEFINED) {
                        m_directions[n.first.first][n.first.second] = n.second;
                        q.push(n.first);
                    }
                }
            }
        }
    }
}

void field::move_character(character* c, geo::i_point coords) {
    m_cells[c->coords().first][c->coords().second]->set_entity(nullptr);
    delete m_cells[coords.first][coords.second]->get_entity();
    m_cells[coords.first][coords.second]->set_entity(c);
    c->set_coords(coords);
}

void field::handle_character_action(character* c, action act) {

    geo::i_point next_coords;

    if (act.m_by_dir) {
        switch (act.m_dir) {
            case direction::UP:
                next_coords = { c->coords().first, c->coords().second - 1 };
                break;
            case direction::DOWN:
                next_coords = { c->coords().first, c->coords().second + 1 };
                break;
            case direction::LEFT:
                next_coords = { c->coords().first - 1, c->coords().second };
                break;
            case direction::RIGHT:
                next_coords = { c->coords().first + 1, c->coords().second };
                break;
            case direction::NONE:
            case direction::UNDEFINED:
                return;
        }
    } else {
        next_coords = act.m_coords;
    }

    if (next_coords.first < 0 || next_coords.first >= width())
        return;
    if (next_coords.second < 0 || next_coords.second >= height())
        return;

    cell* cel = m_cells[next_coords.first][next_coords.second];

    if (cel->type() == cell::WALL)
        return;

    entity* ent = cel->get_entity();

    switch (act.m_type) {
        case action::MOVE:
            if (ent == nullptr)
                move_character(c, next_coords);
            break;
        case action::ATTACK:
            if (ent == nullptr) {
                break;
            } else {
                switch (ent->type()) {
                    case entity::PLAYER:
                    case entity::ENEMY:
                        if (c->type() != ent->type() || act.m_friendly_fire) {
                            c->attack((character*)ent);
                            check_if_character_dead((character*)ent);
                        }
                        break;
                    case entity::ARTIFACT:
                        c->get_artifact((artifact*) ent);
                        cel->set_entity(nullptr);
                        move_character(c, next_coords);
                        break;
                    default:
                        break;
                }
            }
            break;
        case action::TRY_TO_MOVE_ELSE_ATTACK:
            if (ent == nullptr) {
                move_character(c, next_coords);
            } else {
                switch (ent->type()) {
                    case entity::PLAYER:
                    case entity::ENEMY:
                        if (c->type() != ent->type() || act.m_friendly_fire) {
                            c->attack((character*)ent);
                            check_if_character_dead((character*)ent);
                        }
                        break;
                    case entity::ARTIFACT:
                        c->get_artifact((artifact*) ent);
                        cel->set_entity(nullptr);
                        move_character(c, next_coords);
                        break;
                    default:
                        break;
                }
            }
            break;
    }
}

void field::players_turn() {
    handle_character_action(m_player, { action::TRY_TO_MOVE_ELSE_ATTACK, m_player->dir() });
    if (m_player->dir() != direction::NONE && m_player->dir() != direction::UNDEFINED)
        mark_directions();
}

void field::enemies_turn() {
    for (enemy* e : m_enemies)
        handle_character_action(e, e->get_action(*this));
}

void field::check_if_character_dead(character* c) {
    if (c->dead()) {
        if (c == m_player) {
            m_game_condition = game_condition::LOSE;
        } else if (c->type() == entity::ENEMY) {
            delete_enemy((enemy*)c);
        }
    }
}

field::field(int id)
    : m_id(id), m_width(field_templates[id].m_width), m_height(field_templates[id].m_height),
    m_entry(field_templates[id].m_entry), m_exit(field_templates[id].m_exit),
    m_cells(m_width, m_height), m_directions(m_width, m_height),
    m_player(new player(m_entry)),
    m_enemies(), m_artifacts() {

    for (int x = 0; x < m_width; ++x) {
        for (int y = 0; y < m_height; ++y) {
            char c = field_templates[id].m_cells[y][x];
            switch (c) {
                case CELL_GROUND_SYMBOL:
                    m_cells[x][y] = new cell(cell::GROUND);
                    break;
                case CELL_WALL_SYMBOL:
                    m_cells[x][y] = new cell(cell::WALL);
                    break;
                default:
                    throw std::runtime_error(UNKNOWN_CELL_SYMBOL);
            }
        }
    }

    field_templates[id].enemies_generator(*this);
    field_templates[id].artifacts_generator(*this);

    move_character(m_player, m_entry);
    mark_directions();
}

field::~field() {
//    m_cells[m_player->coords().first][m_player->coords().second]->set_entity(nullptr);
//    delete m_player;
//    while (!m_enemies.empty())
//        delete_enemy(0);
//    while (!m_artifacts.empty())
//        delete_artifact(0);
    for (int x = 0; x < width(); ++x)
        for (int y = 0; y < height(); ++y)
            delete m_cells[x][y];
}

void field::send_sygnal(sygnal signal) {
    switch (signal) {
        case sygnal::UP:
            m_player->set_dir(direction::UP);
            break;
        case sygnal::DOWN:
            m_player->set_dir(direction::DOWN);
            break;
        case sygnal::LEFT:
            m_player->set_dir(direction::LEFT);
            break;
        case sygnal::RIGHT:
            m_player->set_dir(direction::RIGHT);
            break;
        case sygnal::STEP:
            step();
            break;
        default:
            throw std::runtime_error(UNKNOWN_SIGNAL_ERROR);
    }
}

int field::width() {
    return m_width;
}

int field::height() {
    return m_height;
}

cell::cell_type field::get_cell_type(int x, int y) const {
    return m_cells[x][y]->type();
}

const player& field::get_player() const {
    return *m_player;
}

const vector<enemy*> field::get_enemies() const {
    return m_enemies;
}

const vector<artifact*> field::get_artifacts() const {
    return m_artifacts;
}

geo::i_point field::get_entry_coords() const {
    return m_entry;
}

geo::i_point field::get_exit_coords() const {
    return m_exit;
}

game_condition field::get_game_condition() const {
    return m_game_condition;
}

void field::add_enemy(enemy* en) {
    m_enemies.add(en);
    m_cells[en->coords().first][en->coords().second]->set_entity(en);
}

void field::add_artifact(artifact* art) {
    m_artifacts.add(art);
    m_cells[art->coords().first][art->coords().second]->set_entity(art);
}

enemy* field::remove_enemy(int index) {
    enemy* ret = m_enemies[index];
    m_enemies.remove(index);
    m_cells[ret->coords().first][ret->coords().second]->set_entity(nullptr);
    return ret;
}

void field::delete_enemy(int index) {
    delete remove_enemy(index);
}

artifact* field::remove_artifact(int index) {
    artifact* ret = m_artifacts[index];
    m_artifacts.remove(index);
    m_cells[ret->coords().first][ret->coords().second]->set_entity(nullptr);
    return ret;
}

void field::delete_artifact(int index) {
    delete remove_artifact(index);
}

enemy* field::remove_enemy(enemy* ptr) {
    for (int i = 0; i < m_enemies.size(); ++i) {
        if (m_enemies[i] == ptr) {
            return remove_enemy(i);
        }
    }
    return nullptr;
}

void field::delete_enemy(enemy* ptr) {
    delete remove_enemy(ptr);
}

artifact* field::remove_artifact(artifact* ptr) {
    for (int i = 0; i < m_artifacts.size(); ++i) {
        if (m_artifacts[i] == ptr) {
            return remove_artifact(i);
        }
    }
    return nullptr;
}

void field::delete_artifact(artifact* ptr) {
    delete remove_artifact(ptr);
}

void field::step() {
    if (m_game_condition != game_condition::RUNNING)
        return;
    players_turn();
    if (m_player->coords() == m_exit) {
        m_game_condition = game_condition::WIN;
        return;
    }
    enemies_turn();
    m_player->set_dir(direction::NONE);
}