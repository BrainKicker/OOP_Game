#ifndef CPP_MY_LIB_STRING_H
#define CPP_MY_LIB_STRING_H

#include <iostream>

#include "../vector/Vector.h"
#include "../../utils/string_utils.h"

template <typename T>
class basic_string;

using string = basic_string<char>;

using wstring = basic_string<wchar_t>;

template <typename T>
class basic_string : public Vector<T> {
protected:
    void __copy(const T* arr);
public:
    basic_string(const T* arr = nullptr);

    T* cstr();
    const T* cstr() const;

    basic_string<T>& operator=(const T* arr);

    basic_string<T> operator+(const T* arr);
    basic_string<T> operator+(const basic_string<T>& other);

    basic_string<T>& operator+=(const T* arr);
    basic_string<T>& operator+=(const basic_string<T>& other);

    friend std::ostream& operator<<(std::ostream& out, const string& str);

    friend std::wostream& operator<<(std::wostream& out, const wstring& str);
};

template <typename T>
void basic_string<T>::__copy(const T* arr) {
    int len = string_utils::len<T>(arr);
    Vector<T>::resize(len);
    for (int i = 0; i <= len; ++i)
        Vector<T>::operator[](i) = arr[i];
}

template <typename T>
basic_string<T>::basic_string(const T* arr) {
    __copy(arr);
}

template<typename T>
T *basic_string<T>::cstr() {
    return Vector<T>::arr();
}

template<typename T>
const T *basic_string<T>::cstr() const {
    return Vector<T>::arr();
}

template <typename T>
basic_string<T>& basic_string<T>::operator=(const T* arr) {
    __copy(arr);
    return *this;
}

template <typename T>
basic_string<T> basic_string<T>::operator+(const T* arr) {
    return operator+(basic_string<T>(arr));
}

template <typename T>
basic_string<T> basic_string<T>::operator+(const basic_string<T>& other) {
    return basic_string<T>(*this) += other;
}

template <typename T>
basic_string<T>& basic_string<T>::operator+=(const T* arr) {
    operator+=(basic_string<T>(arr));
    return *this;
}

template <typename T>
basic_string<T>& basic_string<T>::operator+=(const basic_string<T>& other) {
    Vector<T>::add(other);
    return *this;
}

#endif //CPP_MY_LIB_STRING_H