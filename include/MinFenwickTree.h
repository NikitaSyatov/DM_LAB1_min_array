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
    std::vector<T> arr;
    FenwickTree<T, false> forwardTree;  // Минимумы на отрезках [i-lowbit(i)+1, i]
    FenwickTree<T, true> backwardTree;  // Минимумы на отрезках [i, i+lowbit(i)-1]
    int n;

    inline int lowbit(int index) const
    {
        return index & -index;
    }

public:
    MinFenwickTree(const std::vector<T>& input);

    T query(int l, int r);
};

#endif // MIN_FENWICK_TREE_H