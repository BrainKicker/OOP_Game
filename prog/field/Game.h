#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <memory>

#include "field.h"

template <int field_id>
class Game {

private:

    std::shared_ptr<field> m_field;

public:

    Game(std::shared_ptr<Logger> logger = nullptr);

    std::shared_ptr<field> get_field();
    const std::shared_ptr<field>& get_field() const;
};

template <int field_id>
Game<field_id>::Game(std::shared_ptr<Logger> logger) : m_field(new field(field_settings<field_id>{}, logger)) {}

template <int field_id>
std::shared_ptr<field> Game<field_id>::get_field() {
    return m_field;
}

template <int field_id>
const std::shared_ptr<field>& Game<field_id>::get_field() const {
    return m_field;
}

#endif //GAME_GAME_H