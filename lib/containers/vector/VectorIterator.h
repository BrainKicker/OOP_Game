#ifndef CPP_MY_LIB_VECTOR_ITERATOR_H
#define CPP_MY_LIB_VECTOR_ITERATOR_H

#include "Vector.h"

template <typename T>
class RVectorIterator;

template <typename T>
class VectorIterator : public std::iterator<std::random_access_iterator_tag, T> {

    template <typename R>
    friend class Vector;

    T* m_cur;

    explicit VectorIterator(T* start);

public:

    RVectorIterator<T>& reverse();

    T& operator*();

    VectorIterator<T> operator+(int n) const;
    int operator-(const VectorIterator<T>& other) const;

    VectorIterator<T>& operator++();
    VectorIterator<T> operator++(int);
    VectorIterator<T>& operator+=(int n);

    VectorIterator<T>& operator--();
    VectorIterator<T> operator--(int);
    VectorIterator<T>& operator-=(int n);

    bool operator==(const VectorIterator<T>& other) const;
    bool operator!=(const VectorIterator<T>& other) const;
};

template <typename T>
class RVectorIterator : public std::iterator<std::random_access_iterator_tag, T> {

    template <typename R>
    friend class vector;

    T* m_cur;

    explicit RVectorIterator(T* start);

public:

    VectorIterator<T>& reverse();

    T& operator*();

    RVectorIterator<T> operator+(int n) const;
    int operator-(const RVectorIterator<T>& other) const;

    RVectorIterator<T>& operator++();
    RVectorIterator<T> operator++(int);
    RVectorIterator<T>& operator+=(int n);

    RVectorIterator<T>& operator--();
    RVectorIterator<T> operator--(int);
    RVectorIterator<T>& operator-=(int n);

    bool operator==(const RVectorIterator<T>& other) const;
    bool operator!=(const RVectorIterator<T>& other) const;
};

template <typename T>
VectorIterator<T>::VectorIterator(T* start) : m_cur(start) {}

template <typename T>
RVectorIterator<T>& VectorIterator<T>::reverse() {
    return RVectorIterator<T>(m_cur);
}

template <typename T>
T& VectorIterator<T>::operator*() {
    return *m_cur;
}

template <typename T>
VectorIterator<T> VectorIterator<T>::operator+(int n) const {
    return VectorIterator<T>(m_cur) += n;
}

template <typename T>
int VectorIterator<T>::operator-(const VectorIterator<T>& other) const {
    return m_cur - other.m_cur;
}

template <typename T>
VectorIterator<T>& VectorIterator<T>::operator++() {
    ++m_cur;
    return *this;
}

template <typename T>
VectorIterator<T> VectorIterator<T>::operator++(int) {
    VectorIterator<T> tmp(m_cur);
    ++m_cur;
    return tmp;
}

template <typename T>
VectorIterator<T>& VectorIterator<T>::operator+=(int n) {
    m_cur += n;
    return *this;
}

template <typename T>
VectorIterator<T>& VectorIterator<T>::operator--() {
    --m_cur;
    return *this;
}

template <typename T>
VectorIterator<T> VectorIterator<T>::operator--(int) {
    VectorIterator<T> tmp(m_cur);
    --m_cur;
    return tmp;
}

template <typename T>
VectorIterator<T>& VectorIterator<T>::operator-=(int n) {
    m_cur -= n;
    return *this;
}

template <typename T>
bool VectorIterator<T>::operator==(const VectorIterator<T>& other) const {
    return m_cur == other.m_cur;
}

template <typename T>
bool VectorIterator<T>::operator!=(const VectorIterator<T>& other) const {
    return !operator==(other);
}

template <typename T>
RVectorIterator<T>::RVectorIterator(T* start) : m_cur(start) {}

template <typename T>
VectorIterator<T>& RVectorIterator<T>::reverse() {
    return VectorIterator<T>(m_cur);
}

template <typename T>
T& RVectorIterator<T>::operator*() {
    return *m_cur;
}

template <typename T>
RVectorIterator<T> RVectorIterator<T>::operator+(int n) const {
    return RVectorIterator<T>(m_cur) += n;
}

template <typename T>
int RVectorIterator<T>::operator-(const RVectorIterator<T>& other) const {
    return m_cur - other.m_cur;
}

template <typename T>
RVectorIterator<T>& RVectorIterator<T>::operator++() {
    --m_cur;
    return *this;
}

template <typename T>
RVectorIterator<T> RVectorIterator<T>::operator++(int) {
    VectorIterator<T> tmp(m_cur);
    --m_cur;
    return tmp;
}

template <typename T>
RVectorIterator<T>& RVectorIterator<T>::operator+=(int n) {
    m_cur -= n;
    return *this;
}

template <typename T>
RVectorIterator<T>& RVectorIterator<T>::operator--() {
    ++m_cur;
    return *this;
}

template <typename T>
RVectorIterator<T> RVectorIterator<T>::operator--(int) {
    VectorIterator<T> tmp(m_cur);
    ++m_cur;
    return tmp;
}

template <typename T>
RVectorIterator<T>& RVectorIterator<T>::operator-=(int n) {
    m_cur += n;
    return *this;
}

template <typename T>
bool RVectorIterator<T>::operator==(const RVectorIterator<T>& other) const {
    return m_cur == other.m_cur;
}

template <typename T>
bool RVectorIterator<T>::operator!=(const RVectorIterator<T>& other) const {
    return !operator==(other);
}

#endif //CPP_MY_LIB_VECTOR_ITERATOR_H