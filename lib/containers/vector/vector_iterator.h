#ifndef CPP_MY_LIB_VECTOR_ITERATOR_H
#define CPP_MY_LIB_VECTOR_ITERATOR_H

#include "vector.h"

template <typename T>
class r_vector_iterator;

template <typename T>
class vector_iterator : public std::iterator<std::random_access_iterator_tag, T> {

    template <typename R>
    friend class vector;

    T* m_cur;

    explicit vector_iterator(T* start);

public:

    r_vector_iterator<T>& reverse();

    T& operator*();

    vector_iterator<T> operator+(int n) const;
    int operator-(const vector_iterator<T>& other) const;

    vector_iterator<T>& operator++();
    vector_iterator<T> operator++(int);
    vector_iterator<T>& operator+=(int n);

    vector_iterator<T>& operator--();
    vector_iterator<T> operator--(int);
    vector_iterator<T>& operator-=(int n);

    bool operator==(const vector_iterator<T>& other) const;
    bool operator!=(const vector_iterator<T>& other) const;
};

template <typename T>
class r_vector_iterator : public std::iterator<std::random_access_iterator_tag, T> {

    template <typename R>
    friend class vector;

    T* m_cur;

    explicit r_vector_iterator(T* start);

public:

    vector_iterator<T>& reverse();

    T& operator*();

    r_vector_iterator<T> operator+(int n) const;
    int operator-(const r_vector_iterator<T>& other) const;

    r_vector_iterator<T>& operator++();
    r_vector_iterator<T> operator++(int);
    r_vector_iterator<T>& operator+=(int n);

    r_vector_iterator<T>& operator--();
    r_vector_iterator<T> operator--(int);
    r_vector_iterator<T>& operator-=(int n);

    bool operator==(const r_vector_iterator<T>& other) const;
    bool operator!=(const r_vector_iterator<T>& other) const;
};

template <typename T>
vector_iterator<T>::vector_iterator(T* start) : m_cur(start) {}

template <typename T>
r_vector_iterator<T>& vector_iterator<T>::reverse() {
    return r_vector_iterator<T>(m_cur);
}

template <typename T>
T& vector_iterator<T>::operator*() {
    return *m_cur;
}

template <typename T>
vector_iterator<T> vector_iterator<T>::operator+(int n) const {
    return vector_iterator<T>(m_cur) += n;
}

template <typename T>
int vector_iterator<T>::operator-(const vector_iterator<T>& other) const {
    return m_cur - other.m_cur;
}

template <typename T>
vector_iterator<T>& vector_iterator<T>::operator++() {
    ++m_cur;
    return *this;
}

template <typename T>
vector_iterator<T> vector_iterator<T>::operator++(int) {
    vector_iterator<T> tmp(m_cur);
    ++m_cur;
    return tmp;
}

template <typename T>
vector_iterator<T>& vector_iterator<T>::operator+=(int n) {
    m_cur += n;
    return *this;
}

template <typename T>
vector_iterator<T>& vector_iterator<T>::operator--() {
    --m_cur;
    return *this;
}

template <typename T>
vector_iterator<T> vector_iterator<T>::operator--(int) {
    vector_iterator<T> tmp(m_cur);
    --m_cur;
    return tmp;
}

template <typename T>
vector_iterator<T>& vector_iterator<T>::operator-=(int n) {
    m_cur -= n;
    return *this;
}

template <typename T>
bool vector_iterator<T>::operator==(const vector_iterator<T>& other) const {
    return m_cur == other.m_cur;
}

template <typename T>
bool vector_iterator<T>::operator!=(const vector_iterator<T>& other) const {
    return !operator==(other);
}

template <typename T>
r_vector_iterator<T>::r_vector_iterator(T* start) : m_cur(start) {}

template <typename T>
vector_iterator<T>& r_vector_iterator<T>::reverse() {
    return vector_iterator<T>(m_cur);
}

template <typename T>
T& r_vector_iterator<T>::operator*() {
    return *m_cur;
}

template <typename T>
r_vector_iterator<T> r_vector_iterator<T>::operator+(int n) const {
    return r_vector_iterator<T>(m_cur) += n;
}

template <typename T>
int r_vector_iterator<T>::operator-(const r_vector_iterator<T>& other) const {
    return m_cur - other.m_cur;
}

template <typename T>
r_vector_iterator<T>& r_vector_iterator<T>::operator++() {
    --m_cur;
    return *this;
}

template <typename T>
r_vector_iterator<T> r_vector_iterator<T>::operator++(int) {
    vector_iterator<T> tmp(m_cur);
    --m_cur;
    return tmp;
}

template <typename T>
r_vector_iterator<T>& r_vector_iterator<T>::operator+=(int n) {
    m_cur -= n;
    return *this;
}

template <typename T>
r_vector_iterator<T>& r_vector_iterator<T>::operator--() {
    ++m_cur;
    return *this;
}

template <typename T>
r_vector_iterator<T> r_vector_iterator<T>::operator--(int) {
    vector_iterator<T> tmp(m_cur);
    ++m_cur;
    return tmp;
}

template <typename T>
r_vector_iterator<T>& r_vector_iterator<T>::operator-=(int n) {
    m_cur += n;
    return *this;
}

template <typename T>
bool r_vector_iterator<T>::operator==(const r_vector_iterator<T>& other) const {
    return m_cur == other.m_cur;
}

template <typename T>
bool r_vector_iterator<T>::operator!=(const r_vector_iterator<T>& other) const {
    return !operator==(other);
}

#endif //CPP_MY_LIB_VECTOR_ITERATOR_H