#include "cell.h"

cell::cell(cell::cell_type type, entity* ent) : m_type(type), m_entity(ent) {}

cell::~cell() {
    delete m_entity;
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

void cell::set_entity(class entity* ent) {
    if (ent != nullptr)
        m_entity_type = ent->type();
    else
        m_entity_type = entity::NONE;
    m_entity = ent;
}