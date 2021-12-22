#ifndef GAME_TYPE_UTILS_H
#define GAME_TYPE_UTILS_H

#include <typeinfo>
#include <typeindex>

namespace type_utils {

    template <typename T>
    const std::type_info& get_type(const T& object);

    template <typename R, typename T>
    bool instanceof(const T& object);

    template <typename T, typename R>
    bool same_type(const T& obj1, const R& obj2);

}

template <typename T>
const std::type_info& type_utils::get_type(const T& object) {
    return typeid(object);
}

template <typename R, typename T>
bool type_utils::instanceof(const T& object) {
    return dynamic_cast<const R*>(&object) != nullptr;
}

template <typename T, typename R>
bool type_utils::same_type(const T& obj1, const R& obj2) {
    return typeid(obj1) == typeid(obj2);
}

#endif //GAME_TYPE_UTILS_H