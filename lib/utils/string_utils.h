#ifndef CPP_MY_LIB_STRING_UTILS_H
#define CPP_MY_LIB_STRING_UTILS_H

class string_utils {
public:
    template <typename T>
    static int len(const T* arr);
};

template <typename T>
int string_utils::len(const T* arr) {
    if (arr == nullptr)
        return 0;
    int count = 0;
    while ((int)*arr != 0) {
        ++arr;
        ++count;
    }
    return count;
}

#endif //CPP_MY_LIB_STRING_UTILS_H