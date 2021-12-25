#ifndef GAME_FIELD_SETTINGS_H
#define GAME_FIELD_SETTINGS_H

template <int field_id>
class field_settings {
public:
    int get_field_id();
};

template <int field_id>
int field_settings<field_id>::get_field_id() {
    return field_id;
}

#endif //GAME_FIELD_SETTINGS_H