#ifndef CPP_MY_LIB_LIST_H
#define CPP_MY_LIB_LIST_H

#include <exception>

#include "../../utils/memory_utils.h"

template <typename T>
class List {

    class node {
        friend class List<T>;
        node* m_left;
        node* m_right;
        T m_data;
    public:
        node(const T& t, node* left = nullptr, node* right = nullptr);
        node(T&& t, node* left = nullptr, node* right = nullptr);
    };

    node* m_first = nullptr;
    node* m_last = nullptr;
    int m_size = 0;

    void assume_not_empty();

public:

    List();
    ~List();

    void add(const T& t);
    void add(T&& t);
    void add_first(const T& t);
    void add_first(T&& t);

    void remove_first();
    void remove_last();

    T& first();
    const T& first() const;

    T& last();
    const T& last() const;

    int size();
    bool empty();
};

template <typename T>
List<T>::node::node(const T& t, node* left, node* right) : m_data(t), m_left(left), m_right(right) {}

template <typename T>
List<T>::node::node(T&& t, List::node* left, List::node* right) : m_data(std::move(t)), m_left(left), m_right(right) {}

template <typename T>
void List<T>::assume_not_empty() {
    if (empty())
        throw std::out_of_range("List is empty");
}

template <typename T>
List<T>::List() {}

template <typename T>
List<T>::~List() {
    while (m_size)
        remove_last();
}

template <typename T>
void List<T>::add(const T& t) {
    node* new_node = new node(t, m_last);
    if (m_size == 0) {
        m_first = m_last = new_node;
    } else {
        m_last->m_right = new_node;
        m_last = new_node;
    }
    ++m_size;
}

template <typename T>
void List<T>::add(T&& t) {
    node* new_node = new node(std::move(t), m_last);
    if (m_size == 0) {
        m_first = m_last = new_node;
    } else {
        m_last->m_right = new_node;
        m_last = new_node;
    }
    ++m_size;
}

template <typename T>
void List<T>::add_first(const T& t) {
    node* new_node = new node(t, nullptr, m_first);
    if (m_size == 0) {
        m_first = m_last = new_node;
    } else {
        m_first->m_left = new_node;
        m_first = new_node;
    }
    ++m_size;
}

template <typename T>
void List<T>::add_first(T&& t) {
    node* new_node = new node(std::move(t), nullptr, m_first);
    if (m_size == 0) {
        m_first = m_last = new_node;
    } else {
        m_first->m_left = new_node;
        m_first = new_node;
    }
    ++m_size;
}

template <typename T>
void List<T>::remove_first() {
    assume_not_empty();
    memory_utils::destruct(&m_first->m_data);
    if (m_size == 1) {
        delete m_first;
        m_first = m_last = nullptr;
    } else {
        m_first = m_first->m_right;
        delete m_first->m_left;
        m_first->m_left = nullptr;
    }
    --m_size;
}

template <typename T>
void List<T>::remove_last() {
    assume_not_empty();
    memory_utils::destruct(&m_last->m_data);
    if (m_size == 1) {
        delete m_last;
        m_first = m_last = nullptr;
    } else {
        m_last = m_last->m_left;
        delete m_last->m_right;
        m_last->m_right = nullptr;
    }
    --m_size;
}

template <typename T>
T& List<T>::first() {
    assume_not_empty();
    return m_first->m_data;
}

template <typename T>
const T& List<T>::first() const {
    assume_not_empty();
    return m_first->m_data;
}

template <typename T>
T& List<T>::last() {
    assume_not_empty();
    return m_last->m_data;
}

template <typename T>
const T& List<T>::last() const {
    assume_not_empty();
    return m_last->m_data;
}

template <typename T>
int List<T>::size() {
    return m_size;
}

template <typename T>
bool List<T>::empty() {
    return m_size == 0;
}

#endif //CPP_MY_LIB_LIST_H