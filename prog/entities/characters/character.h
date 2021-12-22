#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

#include "../../../lib/containers/vector/Vector.h"

#include "../entity.h"

class artifact; // pre-declaration

class character : public entity {

    friend class artifact;

protected:

    int m_max_hp;
    int m_hp;
    int m_damage;

    bool m_melee;

    bool m_alive;

    Vector<artifact*> m_artifacts {};

    void print(std::ostream &out) const override;

public:

    inline static const int
            default_initial_max_hp = 100,
            default_initial_hp = 100,
            default_initial_damage = 10;
    inline static const bool
            default_initial_melee = true;

    character(
            geo::i_point coords = { -1, -1 },
            int max_hp = default_initial_max_hp,
            int hp = default_initial_hp,
            int damage = default_initial_damage,
            bool melee = default_initial_melee);

    ~character() override;

    void check_max_hp();
    void check_hp();
    void check_damage();

    int max_hp() const;
    int hp() const;
    int damage() const;

    bool melee() const;
    bool range() const;

    bool alive() const;
    bool dead() const;

    void attack(character* other);

    void get_artifact(artifact* art);

    [[nodiscard]] artifact* remove_artifact(int index);
    void delete_artifact(int index);

    [[nodiscard]] artifact* remove_artifact_by_id(int id);
    void delete_artifact_by_id(int id);
};

#endif //GAME_CHARACTER_H