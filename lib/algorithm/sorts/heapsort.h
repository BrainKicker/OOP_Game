#ifndef CPP_MY_LIB_HEAPSORT_H
#define CPP_MY_LIB_HEAPSORT_H

#include "../comparator/comparator.h"

template <typename Iterator>
using ValueType = typename std::iterator_traits<Iterator>::value_type;

template <typename Iterator>
void heapsort(Iterator begin, Iterator end, const comparator<ValueType<Iterator>>& comp = less<ValueType<Iterator>>) {

    int size = end - begin;

    std::function<ValueType<Iterator>&(int)> get = [&](int index) -> ValueType<Iterator>& {
        return *(begin + index);
    };

    std::function<void(int)> correct_down = [&](int i) {
        int ch1 = 2 * i + 1;
        if (ch1 >= size)
            return;
        int ch2 = ch1 + 1;
        if (ch2 == size)
            ch2 = ch1;
        if (!comp(get(ch1), get(i)) || !comp(get(ch2), get(i))) {
            if (!comp(get(ch1), get(ch2))) {
                std::swap(get(ch1), get(i));
                correct_down(ch1);
            } else {
                std::swap(get(ch2), get(i));
                correct_down(ch2);
            }
        }
    };
    
    std::function<void(int)> correct_up = [&](int i) {
        if (i <= 0)
            return;
        int p = (i - 1) >> 1;
        if (!comp(get(i), get(p))) {
            std::swap(get(i), get(p));
            correct_up(p);
        }
    };

    for (int i = 0; i < size; ++i)
        correct_up(i);

    while (size--) {
        std::swap(get(0), get(size));
        correct_down(0);
    }
}

#endif //CPP_MY_LIB_HEAPSORT_H