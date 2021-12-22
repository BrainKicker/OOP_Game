#ifndef CPP_MY_LIB_MATRIX_H
#define CPP_MY_LIB_MATRIX_H

#include <iostream>

#include "../vector/Vector.h"

template <typename T>
class Matrix {

public:
    using Column = Vector<T>;

    using Iterator = typename Vector<Column>::Iterator;
    using ConstIterator = typename Vector<Column>::ConstIterator;
    using RIterator = typename Vector<Column>::RIterator;
    using RConstIterator = typename Vector<Column>::RConstIterator;

private:
    int m_width = 0, m_height = 0;
    Vector<Column> m_matr{};

    void __copy(const Matrix<T>& other);
    void __move(Matrix<T>&& other);

public:

    Matrix(int width, int height);
    Matrix(const std::initializer_list<Column>& initializerList);
    Matrix(const Matrix<T>& other);
    Matrix(Matrix<T>&& other);

    int width() const;
    int height() const;

    Column& operator[](int index);
    const Column& operator[](int index) const;

    Matrix<T>& operator=(const std::initializer_list<Vector<T>>& initializerList);
    Matrix<T>& operator=(const Matrix<T>& other);
    Matrix<T>& operator=(Matrix<T>&& other);

    template <typename R>
    friend std::ostream& operator<<(std::ostream& out, const Matrix<R>& m);

    Iterator begin();
    Iterator end();
    RIterator rbegin();
    RIterator rend();
    Iterator from(int index);
    RIterator rfrom(int index);

    ConstIterator begin() const;
    ConstIterator end() const;
    RConstIterator rbegin() const;
    RConstIterator rend() const;
    ConstIterator from(int index) const;
    RConstIterator rfrom(int index) const;
};

template <typename T>
void Matrix<T>::__copy(const Matrix<T>& other) {
    m_width = other.m_width;
    m_height = other.m_height;
    m_matr = other.m_matr;
}

template <typename T>
void Matrix<T>::__move(Matrix<T>&& other) {
    m_width = other.m_width;
    m_height = other.m_height;
    m_matr = std::move(other.m_matr);
    other.m_width = 0;
    other.m_height = 0;
}

template <typename T>
Matrix<T>::Matrix(int width, int height) : m_width(width), m_height(height), m_matr(width) {
    m_matr.resize(width);
    for (Column& c : m_matr)
        c.resize(height);
}

template <typename T>
Matrix<T>::Matrix(const std::initializer_list<Column>& initializerList) {
    operator=(initializerList);
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other) {
    __copy(other);
}

template <typename T>
Matrix<T>::Matrix(Matrix<T>&& other) {
    __move(std::move(other));
}

template <typename T>
int Matrix<T>::width() const {
    return m_width;
}

template <typename T>
int Matrix<T>::height() const {
    return m_height;
}

template <typename T>
typename Matrix<T>::Column& Matrix<T>::operator[](int index) {
    return m_matr[index];
}

template <typename T>
const typename Matrix<T>::Column& Matrix<T>::operator[](int index) const {
    return m_matr[index];
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const std::initializer_list<Vector<T>>& initializerList) {
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
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
    if (this != &other) {
        __copy(other);
    }
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other) {
    if (this != &other) {
        __move(std::move(other));
    }
    return *this;
}

template <typename R>
std::ostream& operator<<(std::ostream& out, const Matrix<R>& m) {
    out << "{ width=" << m.m_width << ", height=" << m.m_height << ", elements=" << m.m_matr << " }";
    return out;
}

template<typename T>
typename Matrix<T>::Iterator Matrix<T>::begin() {
    return m_matr.begin();
}

template<typename T>
typename Matrix<T>::Iterator Matrix<T>::end() {
    return m_matr.end();
}

template<typename T>
typename Matrix<T>::RIterator Matrix<T>::rbegin() {
    return m_matr.rbegin();
}

template<typename T>
typename Matrix<T>::RIterator Matrix<T>::rend() {
    return m_matr.rend();
}

template<typename T>
typename Matrix<T>::Iterator Matrix<T>::from(int index) {
    return m_matr.from(index);
}

template<typename T>
typename Matrix<T>::RIterator Matrix<T>::rfrom(int index) {
    return m_matr.rfrom(index);
}

template<typename T>
typename Matrix<T>::ConstIterator Matrix<T>::begin() const {
    return m_matr.begin();
}

template<typename T>
typename Matrix<T>::ConstIterator Matrix<T>::end() const {
    return m_matr.end();
}

template<typename T>
typename Matrix<T>::RConstIterator Matrix<T>::rbegin() const {
    return m_matr.rbegin();
}

template<typename T>
typename Matrix<T>::RConstIterator Matrix<T>::rend() const {
    return m_matr.rend();
}

template<typename T>
typename Matrix<T>::ConstIterator Matrix<T>::from(int index) const {
    return m_matr.from(index);
}

template<typename T>
typename Matrix<T>::RConstIterator Matrix<T>::rfrom(int index) const {
    return m_matr.rfrom(index);
}

#endif //CPP_MY_LIB_MATRIX_H