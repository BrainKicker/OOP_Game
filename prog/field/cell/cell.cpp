#include "cell.h"

cell::cell(cell::cell_type type, entity* ent) : m_type(type) {
    set_entity(ent);
}

cell::~cell() {
    delete m_entity;
    m_entity = nullptr;
    m_entity_type = entity::NONE;
}

cell::cell_type& cell::type() {
    return m_type;
}

const cell::cell_type& cell::type() const {
    return m_type;
}

void cell::set_type(cell::cell_type type) {
    m_type = type;
}

entity*& cell::get_entity() {
    return m_entity;
}

const entity *const & cell::get_entity() const {
    return m_entity;
}

entity::entity_type cell::get_entity_type() const {
    return m_entity_type;
}

void cell::set_entity(class entity* ent) {
    if (ent != nullptr)
        m_entity_type = ent->get_entity_type();
    else
        m_entity_type = entity::NONE;
    m_entity = ent;
}