#ifndef MIN_FENWICK_TREE_H
#define MIN_FENWICK_TREE_H

#include <vector>
#include "FenwickTree.h"

constexpr bool isReversed = true;
constexpr bool isNotReversed = false;

template<typename T>
class MinFenwickTree
{
private:
    const T T_Max = std::numeric_limits<T>::max();
    FenwickTree<T, isReversed> bit;
    FenwickTree<T, isNotReversed> bit_reversed;
    std::vector<T> orig_arr;
    int size;

public:
    MinFenwickTree(const std::vector<int>& arr);

    void update(int idx, T val);

    T query(int l, int r);
};

#endif // MIN_FENWICK_TREE_H