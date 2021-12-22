#ifndef CPP_MY_LIB_QUEUE_H
#define CPP_MY_LIB_QUEUE_H

#include "../list/List.h"

template <typename T>
class Queue {

protected:

    List<T> m_list;

public:

    Queue();

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
Queue<T>::Queue() {}

template <typename T>
void Queue<T>::push(const T& t) {
    m_list.add(t);
}

template <typename T>
void Queue<T>::push(T&& t) {
    m_list.add(std::move(t));
}

template <typename T>
T& Queue<T>::front() {
    return m_list.first();
}

template <typename T>
const T& Queue<T>::front() const {
    return m_list.first();
}

template <typename T>
T& Queue<T>::back() {
    return m_list.last();
}

template <typename T>
const T& Queue<T>::back() const {
    return m_list.last();
}

template <typename T>
T Queue<T>::pop() {
    T t = m_list.first();
    m_list.remove_first();
    return t;
}

template <typename T>
int Queue<T>::size() {
    return m_list.size();
}

template <typename T>
bool Queue<T>::empty() {
    return m_list.empty();
}

#endif //CPP_MY_LIB_QUEUE_H