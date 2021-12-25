#include "cell.h"

cell::cell(cell::cell_type type, entity* ent) : m_type(type) {
    set_entity(ent);
}

cell::~cell() {
    delete m_entity;
    m_entity = nullptr;
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

void cell::set_entity(entity* ent) {
    m_entity = ent;
}

void cell::save(std::ostream& out) const {
    out << m_type << ' ' << m_entity << '\n';
}

void cell::load(std::istream& in) {
    int type;
    in >> type;
    if (in.fail())
        throw load_error{};
    m_type = (cell_type) type;
    uint64_t ent;
    in >> ent;
    if (in.fail())
        throw load_error{};
    m_entity = (entity*) ent;
}