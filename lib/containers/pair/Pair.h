#ifndef CPP_MY_LIB_PAIR_H
#define CPP_MY_LIB_PAIR_H

#include <iostream>
#include <utility>
#include <cstring>

template <typename T, typename R = T>
class Pair {

    void __copy(const Pair<T,R>& other);
    void __move(Pair<T,R>&& other);

public:
    T first{};
    R second{};

    Pair();
    Pair(const T& f, const R& s);
    Pair(const T& f, R&& s);
    Pair(T&& f, const R& s);
    Pair(T&& f, R&& s);
    Pair(const Pair<T,R>& other);
    Pair(Pair<T,R>&& other);

    void swap();

    Pair<T,R>& operator=(const Pair<T,R>& other);
    Pair<T,R>& operator=(Pair<T,R>&& other);

    bool operator==(const Pair<T,R>& other) const;
    bool operator!=(const Pair<T,R>& other) const;

    template <typename T1, typename R1>
    friend std::ostream& operator<<(std::ostream& out, const Pair<T1,R1> p);
};

template <typename T, typename R>
void Pair<T,R>::__copy(const Pair<T,R>& other) {
    first = other.first;
    second = other.second;
}

template <typename T, typename R>
void Pair<T,R>::__move(Pair<T,R>&& other) {
    first = other.first;
    second = other.second;
    memset(&other.first, 0, sizeof(other.first));
    memset(&other.second, 0, sizeof(other.second));
}

template <typename T, typename R>
Pair<T,R>::Pair() = default;

template <typename T, typename R>
Pair<T,R>::Pair(const T& f, const R& s) : first(f), second(s) {}

template <typename T, typename R>
Pair<T,R>::Pair(const T& f, R&& s) : first(f), second(std::move(s)) {}

template <typename T, typename R>
Pair<T,R>::Pair(T&& f, const R& s) : first(std::move(f)), second(s) {}

template <typename T, typename R>
Pair<T,R>::Pair(T&& f, R&& s) : first(std::move(f)), second(std::move(s)) {}

template <typename T, typename R>
Pair<T,R>::Pair(const Pair<T,R>& other) {
    __copy(other);
}

template <typename T, typename R>
Pair<T,R>::Pair(Pair<T,R>&& other) {
    __move(std::move(other));
}

template<typename T, typename R>
void Pair<T, R>::swap() {
    std::swap(first, second);
}

template <typename T, typename R>
Pair<T,R>& Pair<T,R>::operator=(const Pair<T,R>& other) {
    if (this != &other) {
        __copy(other);
    }
    return *this;
}

template <typename T, typename R>
Pair<T,R>& Pair<T,R>::operator=(Pair<T,R>&& other) {
    if (this != &other) {
        __move(std::move(other));
    }
    return *this;
}

template <typename T, typename R>
bool Pair<T,R>::operator==(const Pair<T,R>& other) const {
    return first == other.first && second == other.second;
}

template <typename T, typename R>
bool Pair<T,R>::operator!=(const Pair<T,R>& other) const {
    return !operator==(other);
}

template<typename T1, typename R1>
std::ostream& operator<<(std::ostream& out, const Pair<T1, R1> p) {
    out << "{ " << p.first << ", " << p.second << " }";
    return out;
}

#endif //CPP_MY_LIB_PAIR_H