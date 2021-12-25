#ifndef GAME_CELL_H
#define GAME_CELL_H

#include "../../entities/entity.h"

class cell {
public:

    enum cell_type {
        GROUND,
        WALL
    };

private:

    cell_type m_type;
    entity* m_entity;

public:

    cell(cell_type type, entity* ent = nullptr);

    ~cell();

    cell_type& type();
    const cell_type& type() const;
    void set_type(cell_type type);

    entity*& get_entity();
    const entity *const & get_entity() const;
    void set_entity(class entity* ent);
};

#endif //GAME_CELL_H