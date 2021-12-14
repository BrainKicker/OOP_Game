#ifndef CPP_MY_LIB_PAIR_H
#define CPP_MY_LIB_PAIR_H

#include <iostream>
#include <utility>
#include <cstring>

template <typename T, typename R = T>
class pair {

    void __copy(const pair<T,R>& other);
    void __move(pair<T,R>&& other);

public:
    T first{};
    R second{};

    pair();
    pair(const T& f, const R& s);
    pair(const T& f, R&& s);
    pair(T&& f, const R& s);
    pair(T&& f, R&& s);
    pair(const pair<T,R>& other);
    pair(pair<T,R>&& other);

    void swap();

    pair<T,R>& operator=(const pair<T,R>& other);
    pair<T,R>& operator=(pair<T,R>&& other);

    bool operator==(const pair<T,R>& other) const;
    bool operator!=(const pair<T,R>& other) const;

    template <typename T1, typename R1>
    friend std::ostream& operator<<(std::ostream& out, const pair<T1,R1> p);
};

template <typename T, typename R>
void pair<T,R>::__copy(const pair<T,R>& other) {
    first = other.first;
    second = other.second;
}

template <typename T, typename R>
void pair<T,R>::__move(pair<T,R>&& other) {
    first = other.first;
    second = other.second;
    memset(&other.first, 0, sizeof(other.first));
    memset(&other.second, 0, sizeof(other.second));
}

template <typename T, typename R>
pair<T,R>::pair() = default;

template <typename T, typename R>
pair<T,R>::pair(const T& f, const R& s) : first(f), second(s) {}

template <typename T, typename R>
pair<T,R>::pair(const T& f, R&& s) : first(f), second(std::move(s)) {}

template <typename T, typename R>
pair<T,R>::pair(T&& f, const R& s) : first(std::move(f)), second(s) {}

template <typename T, typename R>
pair<T,R>::pair(T&& f, R&& s) : first(std::move(f)), second(std::move(s)) {}

template <typename T, typename R>
pair<T,R>::pair(const pair<T,R>& other) {
    __copy(other);
}

template <typename T, typename R>
pair<T,R>::pair(pair<T,R>&& other) {
    __move(std::move(other));
}

template<typename T, typename R>
void pair<T, R>::swap() {
    std::swap(first, second);
}

template <typename T, typename R>
pair<T,R>& pair<T,R>::operator=(const pair<T,R>& other) {
    if (this != &other) {
        __copy(other);
    }
    return *this;
}

template <typename T, typename R>
pair<T,R>& pair<T,R>::operator=(pair<T,R>&& other) {
    if (this != &other) {
        __move(std::move(other));
    }
    return *this;
}

template <typename T, typename R>
bool pair<T,R>::operator==(const pair<T,R>& other) const {
    return first == other.first && second == other.second;
}

template <typename T, typename R>
bool pair<T,R>::operator!=(const pair<T,R>& other) const {
    return !operator==(other);
}

template<typename T1, typename R1>
std::ostream& operator<<(std::ostream& out, const pair<T1, R1> p) {
    out << "{ " << p.first << ", " << p.second << " }";
    return out;
}

#endif //CPP_MY_LIB_PAIR_H