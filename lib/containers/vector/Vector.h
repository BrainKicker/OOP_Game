#ifndef CPP_MY_LIB_VECTOR_H
#define CPP_MY_LIB_VECTOR_H

#include <iostream>
#include <iterator>

#include "VectorIterator.h"

#include "../../utils/memory_utils.h"

template <typename T>
class Vector {
public:

    using Iterator = VectorIterator<T>;
    using ConstIterator = VectorIterator<const T>;
    using RIterator = RVectorIterator<T>;
    using RConstIterator = RVectorIterator<const T>;

    static constexpr int initial_capacity = 10;

private:

    int m_size = 0;
    int m_capacity = 0;
    T* m_arr = nullptr;

    void __copy(const Vector<T>& other);
    void __move(Vector<T>&& other);
    void __free();

    void __reserve_more(int n = 1);

protected:

    T* arr();
    const T* arr() const;

public:

    Vector();
    explicit Vector(int n);
    Vector(const std::initializer_list<T>& initializerList);
    Vector(const Vector<T>& other);
    Vector(Vector<T>&& other);

    ~Vector();

    void resize(int n);
    void reserve(int n);
    void clear();

    void add(const T& elem);
    void add(T&& elem);
    void add(const Vector<T>& other);
    void add(Vector<T>&& other);
    void remove(int index);

    int size() const;
    int capacity() const;
    bool empty() const;

    Vector<T>& operator=(const std::initializer_list<T>& initializerList);
    Vector<T>& operator=(const Vector<T>& other);
    Vector<T>& operator=(Vector<T>&& other);

    T& operator[](int index);
    const T& operator[](int index) const;

    Vector<T> operator+(const Vector<T>& other) const;

    Vector<T>& operator+=(const Vector<T>& other);

    bool operator==(const Vector<T>& other);
    bool operator!=(const Vector<T>& other);

    template <typename R>
    friend std::ostream& operator<<(std::ostream& out, const Vector<R>& v);

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
void Vector<T>::__copy(const Vector<T>& other) {
    resize(other.size());
    for (int i = 0; i < m_size; ++i)
        m_arr[i] = other.m_arr[i];
}

template <typename T>
void Vector<T>::__move(Vector<T>&& other) {
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_arr = other.m_arr;
    other.m_size = 0;
    other.m_capacity = 0;
    other.m_arr = nullptr;
}

template <typename T>
void Vector<T>::__free() {
    delete[] m_arr;
    m_arr = nullptr;
    m_size = m_capacity = 0;
}

template<typename T>
void Vector<T>::__reserve_more(int n) {
    reserve(m_capacity * 2 + n);
}

template<typename T>
T* Vector<T>::arr() {
    return m_arr;
}

template<typename T>
const T* Vector<T>::arr() const {
    return m_arr;
}

template <typename T>
Vector<T>::Vector() : Vector<T>(initial_capacity) {}

template <typename T>
Vector<T>::Vector(int n) {
    reserve(n);
}

template <typename T>
Vector<T>::Vector(const std::initializer_list<T>& initializerList) {
    operator=(initializerList);
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other) {
    __copy(other);
}

template <typename T>
Vector<T>::Vector(Vector<T>&& other) {
    __move(std::move(other));
}

template <typename T>
Vector<T>::~Vector() {
    __free();
}

template <typename T>
void Vector<T>::resize(int n) {
    if (n > m_size) {
        reserve(n);
        m_size = n;
    }
    while (m_size > n)
        remove(m_size - 1);
}

template <typename T>
void Vector<T>::reserve(int n) {
    if (n > m_capacity) {
        T* new_arr = new T[n];
        for (int i = 0; i < m_size; ++i)
            new_arr[i] = m_arr[i];
        delete[] m_arr;
        m_capacity = n;
        m_arr = new_arr;
    }
}

template <typename T>
void Vector<T>::clear() {
    resize(0);
}

template <typename T>
void Vector<T>::add(const T& elem) {
    if (m_size + 1 > m_capacity)
        __reserve_more();
    m_arr[m_size] = elem;
    ++m_size;
}

template<typename T>
void Vector<T>::add(T&& elem) {
    if (m_size + 1 > m_capacity)
        __reserve_more();
    m_arr[m_size] = std::move(elem);
    ++m_size;
}

template <typename T>
void Vector<T>::add(const Vector<T>& other) {
    int old_size = size();
    resize(size() + other.size());
    for (int i = old_size; i < size(); ++i)
        operator[](i) = other[i-old_size];
}

template <typename T>
void Vector<T>::add(Vector<T>&& other) {
    int old_size = size();
    resize(size() + other.size());
    for (int i = old_size; i < size(); ++i)
        operator[](i) = std::move(other[i-old_size]);
    other.__free();
    other.m_size = 0;
    other.m_capacity = 0;
}

template <typename T>
void Vector<T>::remove(int index) {
    memory_utils::destruct(m_arr + index);
    for (int i = index + 1; i < m_size; ++i)
        m_arr[i - 1] = m_arr[i];
    --m_size;
}

template <typename T>
int Vector<T>::size() const {
    return m_size;
}

template <typename T>
int Vector<T>::capacity() const {
    return m_capacity;
}

template <typename T>
bool Vector<T>::empty() const {
    return size() == 0;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const std::initializer_list<T>& initializerList) {
    resize(initializerList.size());
    auto iter = initializerList.begin();
    for (int i = 0; i < m_size; ++i, ++iter)
        m_arr[i] = *iter;
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this != &other) {
        __copy(other);
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) {
    if (this != &other) {
        __move(std::move(other));
    }
    return *this;
}

template <typename T>
T& Vector<T>::operator[](int index) {
    return m_arr[index];
}

template <typename T>
const T& Vector<T>::operator[](int index) const {
    return m_arr[index];
}

template <typename T>
Vector<T> Vector<T>::operator+(const Vector<T>& other) const {
    return Vector<T>(*this) += other;
}

template <typename T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& other) {
    add(other);
    return *this;
}

template <typename T>
bool Vector<T>::operator==(const Vector<T>& other) {
    if (size() != other.size())
        return false;
    for (int i = 0; i < size(); ++i)
        if (operator[](i) != other[i])
            return false;
    return true;
}

template <typename T>
bool Vector<T>::operator!=(const Vector<T>& other) {
    return !operator==(other);
}

template <typename R>
std::ostream& operator<<(std::ostream& out, const Vector<R>& v) {
    if (v.size() == 0) {
        out << "{}";
        return out;
    }
    out << "{ ";
    for (int i = 0;;) {
        out << v[i];
        if (++i == v.size())
            break;
        out << ", ";
    }
    out << " }";
    return out;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::begin() {
    return Iterator(m_arr);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::end() {
    return Iterator(m_arr + m_size);
}

template <typename T>
typename Vector<T>::RIterator Vector<T>::rbegin() {
    return RIterator(m_arr + m_size - 1);
}

template <typename T>
typename Vector<T>::RIterator Vector<T>::rend() {
    return RIterator(m_arr - 1);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::from(int index) {
    return Iterator(m_arr + index);
}

template <typename T>
typename Vector<T>::RIterator Vector<T>::rfrom(int index) {
    return RIterator(m_arr + index);
}

template <typename T>
typename Vector<T>::ConstIterator Vector<T>::begin() const {
    return ConstIterator(m_arr);
}

template <typename T>
typename Vector<T>::ConstIterator Vector<T>::end() const {
    return ConstIterator(m_arr + m_size);
}

template <typename T>
typename Vector<T>::RConstIterator Vector<T>::rbegin() const {
    return RConstIterator(m_arr + m_size - 1);
}

template <typename T>
typename Vector<T>::RConstIterator Vector<T>::rend() const {
    return RConstIterator(m_arr - 1);
}

template <typename T>
typename Vector<T>::ConstIterator Vector<T>::from(int index) const {
    return ConstIterator(m_arr + index);
}

template <typename T>
typename Vector<T>::RConstIterator Vector<T>::rfrom(int index) const {
    return RConstIterator(m_arr + index);
}

#endif //CPP_MY_LIB_VECTOR_H