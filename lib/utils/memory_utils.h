#ifndef CPP_MY_LIB_MEMORY_UTILS_H
#define CPP_MY_LIB_MEMORY_UTILS_H

class memory_utils {
public:
    template <typename T>
    static void destruct(T* ptr);
};

template <typename T>
void memory_utils::destruct(T* ptr) {
    ptr->~T();
    ptr = nullptr;
}

#endif //CPP_MY_LIB_MEMORY_UTILS_H