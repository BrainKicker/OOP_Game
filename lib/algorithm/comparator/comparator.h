#ifndef CPP_MY_LIB_COMPARATOR_H
#define CPP_MY_LIB_COMPARATOR_H

#include <functional>

template <typename T>
using comparator = std::function<bool(const T&, const T&)>;

template <typename T>
const comparator<T> less = [](const T& a, const T& b) { return a < b; };
template <typename T>
const comparator<T> nless = [](const T& a, const T& b) { return a >= b; };
template <typename T>
const comparator<T> greater = [](const T& a, const T& b) { return a > b; };
template <typename T>
const comparator<T> ngreater = [](const T& a, const T& b) { return a <= b; };

#endif //CPP_MY_LIB_COMPARATOR_H