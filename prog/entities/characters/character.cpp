#include "character.h"

#include "../artifacts/artifact.h"

character::character(entity_type type, geo::i_point coords, int max_hp, int hp, int damage, bool melee)
: entity(type, coords), m_max_hp(max_hp), m_hp(hp), m_damage(damage), m_melee(melee) {}

character::~character() {
    for (artifact* art : m_artifacts)
        delete art;
}

void character::check_max_hp() {
    if (m_max_hp < 0)
        m_max_hp = 0;
}

void character::check_hp() {
    if (m_hp < 0)
        m_hp = 0;
    else if (m_hp > m_max_hp)
        m_hp = m_max_hp;
    if (m_hp <= 0)
        m_alive = false;
    else
        m_alive = true;
}

void character::check_damage() {
    if (m_damage < 0)
        m_damage = 0;
}

int character::max_hp() const {
    return m_max_hp;
}

int character::hp() const {
    return m_hp;
}

int character::damage() const {
    return m_damage;
}

bool character::melee() const {
    return m_melee;
}

bool character::range() const {
    return !m_melee;
}

bool character::alive() const {
    return m_alive;
}

bool character::dead() const {
    return !m_alive;
}

void character::attack(character* other) {
    other->m_hp -= m_damage;
    other->check_hp();
}

void character::get_artifact(artifact* art) {
    artifact::act(art, this);
    m_artifacts.add(art);
}

[[nodiscard]] artifact* character::remove_artifact(int index) {
    artifact* art = m_artifacts[index];
    artifact::react(art, this);
    m_artifacts.remove(index);
    return art;
}

void character::delete_artifact(int index) {
    delete remove_artifact(index);
}

[[nodiscard]] artifact* character::remove_artifact_by_id(int id) {
    // searching from the end to the beginning
    for (int i = m_artifacts.size() - 1; i >= 0; --i) {
        if (m_artifacts[i]->id() == id) {
            artifact* art = m_artifacts[i];
            artifact::react(art, this);
            m_artifacts.remove(i);
            return art;
        }
    }
    return nullptr;
}

void character::delete_artifact_by_id(int id) {
    delete remove_artifact_by_id(id);
}