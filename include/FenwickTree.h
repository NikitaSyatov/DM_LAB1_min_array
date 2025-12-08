#ifndef FENWICK_TREE_H
#define FENWICK_TREE_H

#include <vector>
#include <limits>
#include <algorithm>

template<typename T, bool isReversed>
class FenwickTree
{
private:
    const T T_Max = std::numeric_limits<T>::max();
    std::vector<T> tree;
    int n;

    inline int lowbit(int index) const
    {
        return index & -index;
    }

public:
    FenwickTree(int size);
    
    void build(const std::vector<T>& arr);
    T get(int idx) const;

    void print() const;
};

#endif // FENWICK_TREE_H