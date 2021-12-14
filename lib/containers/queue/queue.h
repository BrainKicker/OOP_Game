#ifndef CPP_MY_LIB_QUEUE_H
#define CPP_MY_LIB_QUEUE_H

#include "../list/list.h"

template <typename T>
class queue {

protected:

    list<T> m_list;

public:

    queue();

    void push(const T& t);
    void push(T&& t);
    T pop();

    T& front();
    const T& front() const;

    T& back();
    const T& back() const;

    int size();
    bool empty();
};

template <typename T>
queue<T>::queue() {}

template <typename T>
void queue<T>::push(const T& t) {
    m_list.add(t);
}

template <typename T>
void queue<T>::push(T&& t) {
    m_list.add(std::move(t));
}

template <typename T>
T& queue<T>::front() {
    return m_list.first();
}

template <typename T>
const T& queue<T>::front() const {
    return m_list.first();
}

template <typename T>
T& queue<T>::back() {
    return m_list.last();
}

template <typename T>
const T& queue<T>::back() const {
    return m_list.last();
}

template <typename T>
T queue<T>::pop() {
    T t = m_list.first();
    m_list.remove_first();
    return t;
}

template <typename T>
int queue<T>::size() {
    return m_list.size();
}

template <typename T>
bool queue<T>::empty() {
    return m_list.empty();
}

#endif //CPP_MY_LIB_QUEUE_H