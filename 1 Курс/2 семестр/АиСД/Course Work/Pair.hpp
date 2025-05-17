#ifndef PAIR_HPP
#define PAIR_HPP

template<typename T1, typename T2>
struct Pair {
    T1 first;
    T2 second;
    Pair(T1 first, T2 second): first(first), second(second) {}
    Pair() = default;
};

#endif //PAIR_HPP
