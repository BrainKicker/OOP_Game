#ifndef CPP_MY_LIB_MATRIX_H
#define CPP_MY_LIB_MATRIX_H

#include <iostream>

#include "../vector/vector.h"

template <typename T>
class matrix {

public:
    using column = vector<T>;

    using iterator = typename vector<column>::iterator;
    using const_iterator = typename vector<column>::const_iterator;
    using r_iterator = typename vector<column>::r_iterator;
    using r_const_iterator = typename vector<column>::r_const_iterator;

private:
    int m_width = 0, m_height = 0;
    vector<column> m_matr{};

    void __copy(const matrix<T>& other);
    void __move(matrix<T>&& other);

public:

    matrix(int width, int height);
    matrix(const std::initializer_list<column>& initializerList);
    matrix(const matrix<T>& other);
    matrix(matrix<T>&& other);

    int width() const;
    int height() const;

    column& operator[](int index);
    const column& operator[](int index) const;

    matrix<T>& operator=(const std::initializer_list<vector<T>>& initializerList);
    matrix<T>& operator=(const matrix<T>& other);
    matrix<T>& operator=(matrix<T>&& other);

    template <typename R>
    friend std::ostream& operator<<(std::ostream& out, const matrix<R>& m);

    iterator begin();
    iterator end();
    r_iterator rbegin();
    r_iterator rend();
    iterator from(int index);
    r_iterator rfrom(int index);

    const_iterator begin() const;
    const_iterator end() const;
    r_const_iterator rbegin() const;
    r_const_iterator rend() const;
    const_iterator from(int index) const;
    r_const_iterator rfrom(int index) const;
};

template <typename T>
void matrix<T>::__copy(const matrix<T>& other) {
    m_width = other.m_width;
    m_height = other.m_height;
    m_matr = other.m_matr;
}

template <typename T>
void matrix<T>::__move(matrix<T>&& other) {
    m_width = other.m_width;
    m_height = other.m_height;
    m_matr = std::move(other.m_matr);
    other.m_width = 0;
    other.m_height = 0;
}

template <typename T>
matrix<T>::matrix(int width, int height) : m_width(width), m_height(height), m_matr(width) {
    m_matr.resize(width);
    for (column& c : m_matr)
        c.resize(height);
}

template <typename T>
matrix<T>::matrix(const std::initializer_list<column>& initializerList) {
    operator=(initializerList);
}

template <typename T>
matrix<T>::matrix(const matrix<T>& other) {
    __copy(other);
}

template <typename T>
matrix<T>::matrix(matrix<T>&& other) {
    __move(std::move(other));
}

template <typename T>
int matrix<T>::width() const {
    return m_width;
}

template <typename T>
int matrix<T>::height() const {
    return m_height;
}

template <typename T>
typename matrix<T>::column& matrix<T>::operator[](int index) {
    return m_matr[index];
}

template <typename T>
const typename matrix<T>::column& matrix<T>::operator[](int index) const {
    return m_matr[index];
}

template <typename T>
matrix<T>& matrix<T>::operator=(const std::initializer_list<vector<T>>& initializerList) {
    if (initializerList.size() == 0) {
        m_width = m_height = 0;
        m_matr.resize(0);
    } else {
        m_width = initializerList.size();
        m_height = (*initializerList.begin()).size();
        m_matr.resize(m_width);
        auto iter = initializerList.begin();
        for (int i = 0; i < m_width; ++i, ++iter)
            m_matr[i] = std::move(*iter);
    }
}

template <typename T>
matrix<T>& matrix<T>::operator=(const matrix<T>& other) {
    if (this != &other) {
        __copy(other);
    }
    return *this;
}

template <typename T>
matrix<T>& matrix<T>::operator=(matrix<T>&& other) {
    if (this != &other) {
        __move(std::move(other));
    }
    return *this;
}

template <typename R>
std::ostream& operator<<(std::ostream& out, const matrix<R>& m) {
    out << "{ width=" << m.m_width << ", height=" << m.m_height << ", elements=" << m.m_matr << " }";
    return out;
}

template<typename T>
typename matrix<T>::iterator matrix<T>::begin() {
    return m_matr.begin();
}

template<typename T>
typename matrix<T>::iterator matrix<T>::end() {
    return m_matr.end();
}

template<typename T>
typename matrix<T>::r_iterator matrix<T>::rbegin() {
    return m_matr.rbegin();
}

template<typename T>
typename matrix<T>::r_iterator matrix<T>::rend() {
    return m_matr.rend();
}

template<typename T>
typename matrix<T>::iterator matrix<T>::from(int index) {
    return m_matr.from(index);
}

template<typename T>
typename matrix<T>::r_iterator matrix<T>::rfrom(int index) {
    return m_matr.rfrom(index);
}

template<typename T>
typename matrix<T>::const_iterator matrix<T>::begin() const {
    return m_matr.begin();
}

template<typename T>
typename matrix<T>::const_iterator matrix<T>::end() const {
    return m_matr.end();
}

template<typename T>
typename matrix<T>::r_const_iterator matrix<T>::rbegin() const {
    return m_matr.rbegin();
}

template<typename T>
typename matrix<T>::r_const_iterator matrix<T>::rend() const {
    return m_matr.rend();
}

template<typename T>
typename matrix<T>::const_iterator matrix<T>::from(int index) const {
    return m_matr.from(index);
}

template<typename T>
typename matrix<T>::r_const_iterator matrix<T>::rfrom(int index) const {
    return m_matr.rfrom(index);
}

#endif //CPP_MY_LIB_MATRIX_H