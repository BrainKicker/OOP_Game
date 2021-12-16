#ifndef CPP_MY_LIB_VECTOR_H
#define CPP_MY_LIB_VECTOR_H

#include <iostream>
#include <iterator>

#include "vector_iterator.h"

#include "../../utils/memory_utils.h"

template <typename T>
class vector {
public:

    using iterator = vector_iterator<T>;
    using const_iterator = vector_iterator<const T>;
    using r_iterator = r_vector_iterator<T>;
    using r_const_iterator = r_vector_iterator<const T>;

    static constexpr int initial_capacity = 10;

private:

    int m_size = 0;
    int m_capacity = 0;
    T* m_arr = nullptr;

    void __copy(const vector<T>& other);
    void __move(vector<T>&& other);
    void __free();

    void __reserve_more(int n = 1);

protected:

    T* arr();
    const T* arr() const;

public:

    vector();
    explicit vector(int n);
    vector(const std::initializer_list<T>& initializerList);
    vector(const vector<T>& other);
    vector(vector<T>&& other);

    ~vector();

    void resize(int n);
    void reserve(int n);
    void clear();

    void add(const T& elem);
    void add(T&& elem);
    void add(const vector<T>& other);
    void add(vector<T>&& other);
    void remove(int index);

    int size() const;
    int capacity() const;
    bool empty() const;

    vector<T>& operator=(const std::initializer_list<T>& initializerList);
    vector<T>& operator=(const vector<T>& other);
    vector<T>& operator=(vector<T>&& other);

    T& operator[](int index);
    const T& operator[](int index) const;

    vector<T> operator+(const vector<T>& other) const;

    vector<T>& operator+=(const vector<T>& other);

    bool operator==(const vector<T>& other);
    bool operator!=(const vector<T>& other);

    template <typename R>
    friend std::ostream& operator<<(std::ostream& out, const vector<R>& v);

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
void vector<T>::__copy(const vector<T>& other) {
    resize(other.size());
    for (int i = 0; i < m_size; ++i)
        m_arr[i] = other.m_arr[i];
}

template <typename T>
void vector<T>::__move(vector<T>&& other) {
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_arr = other.m_arr;
    other.m_size = 0;
    other.m_capacity = 0;
    other.m_arr = nullptr;
}

template <typename T>
void vector<T>::__free() {
    delete[] m_arr;
    m_arr = nullptr;
    m_size = m_capacity = 0;
}

template<typename T>
void vector<T>::__reserve_more(int n) {
    reserve(m_capacity * 2 + n);
}

template<typename T>
T* vector<T>::arr() {
    return m_arr;
}

template<typename T>
const T* vector<T>::arr() const {
    return m_arr;
}

template <typename T>
vector<T>::vector() : vector<T>(initial_capacity) {}

template <typename T>
vector<T>::vector(int n) {
    reserve(n);
}

template <typename T>
vector<T>::vector(const std::initializer_list<T>& initializerList) {
    operator=(initializerList);
}

template <typename T>
vector<T>::vector(const vector<T>& other) {
    __copy(other);
}

template <typename T>
vector<T>::vector(vector<T>&& other) {
    __move(std::move(other));
}

template <typename T>
vector<T>::~vector() {
    __free();
}

template <typename T>
void vector<T>::resize(int n) {
    if (n > m_size) {
        reserve(n);
        m_size = n;
    }
    while (m_size > n)
        remove(m_size - 1);
}

template <typename T>
void vector<T>::reserve(int n) {
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
void vector<T>::clear() {
    resize(0);
}

template <typename T>
void vector<T>::add(const T& elem) {
    if (m_size + 1 > m_capacity)
        __reserve_more();
    m_arr[m_size] = elem;
    ++m_size;
}

template<typename T>
void vector<T>::add(T&& elem) {
    if (m_size + 1 > m_capacity)
        __reserve_more();
    m_arr[m_size] = std::move(elem);
    ++m_size;
}

template <typename T>
void vector<T>::add(const vector<T>& other) {
    int old_size = size();
    resize(size() + other.size());
    for (int i = old_size; i < size(); ++i)
        operator[](i) = other[i-old_size];
}

template <typename T>
void vector<T>::add(vector<T>&& other) {
    int old_size = size();
    resize(size() + other.size());
    for (int i = old_size; i < size(); ++i)
        operator[](i) = std::move(other[i-old_size]);
    other.__free();
    other.m_size = 0;
    other.m_capacity = 0;
}

template <typename T>
void vector<T>::remove(int index) {
    memory_utils::destruct(m_arr + index);
    for (int i = index + 1; i < m_size; ++i)
        m_arr[i - 1] = m_arr[i];
    --m_size;
}

template <typename T>
int vector<T>::size() const {
    return m_size;
}

template <typename T>
int vector<T>::capacity() const {
    return m_capacity;
}

template <typename T>
bool vector<T>::empty() const {
    return size() == 0;
}

template <typename T>
vector<T>& vector<T>::operator=(const std::initializer_list<T>& initializerList) {
    resize(initializerList.size());
    auto iter = initializerList.begin();
    for (int i = 0; i < m_size; ++i, ++iter)
        m_arr[i] = *iter;
    return *this;
}

template <typename T>
vector<T>& vector<T>::operator=(const vector<T>& other) {
    if (this != &other) {
        __copy(other);
    }
    return *this;
}

template <typename T>
vector<T>& vector<T>::operator=(vector<T>&& other) {
    if (this != &other) {
        __move(std::move(other));
    }
    return *this;
}

template <typename T>
T& vector<T>::operator[](int index) {
    return m_arr[index];
}

template <typename T>
const T& vector<T>::operator[](int index) const {
    return m_arr[index];
}

template <typename T>
vector<T> vector<T>::operator+(const vector<T>& other) const {
    return vector<T>(*this) += other;
}

template <typename T>
vector<T>& vector<T>::operator+=(const vector<T>& other) {
    add(other);
    return *this;
}

template <typename T>
bool vector<T>::operator==(const vector<T>& other) {
    if (size() != other.size())
        return false;
    for (int i = 0; i < size(); ++i)
        if (operator[](i) != other[i])
            return false;
    return true;
}

template <typename T>
bool vector<T>::operator!=(const vector<T>& other) {
    return !operator==(other);
}

template <typename R>
std::ostream& operator<<(std::ostream& out, const vector<R>& v) {
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
typename vector<T>::iterator vector<T>::begin() {
    return iterator(m_arr);
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
    return iterator(m_arr + m_size);
}

template <typename T>
typename vector<T>::r_iterator vector<T>::rbegin() {
    return r_iterator(m_arr + m_size - 1);
}

template <typename T>
typename vector<T>::r_iterator vector<T>::rend() {
    return r_iterator(m_arr - 1);
}

template <typename T>
typename vector<T>::iterator vector<T>::from(int index) {
    return iterator(m_arr + index);
}

template <typename T>
typename vector<T>::r_iterator vector<T>::rfrom(int index) {
    return r_iterator(m_arr + index);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::begin() const {
    return const_iterator(m_arr);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::end() const {
    return const_iterator(m_arr + m_size);
}

template <typename T>
typename vector<T>::r_const_iterator vector<T>::rbegin() const {
    return r_const_iterator(m_arr + m_size - 1);
}

template <typename T>
typename vector<T>::r_const_iterator vector<T>::rend() const {
    return r_const_iterator(m_arr - 1);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::from(int index) const {
    return const_iterator(m_arr + index);
}

template <typename T>
typename vector<T>::r_const_iterator vector<T>::rfrom(int index) const {
    return r_const_iterator(m_arr + index);
}

#endif //CPP_MY_LIB_VECTOR_H