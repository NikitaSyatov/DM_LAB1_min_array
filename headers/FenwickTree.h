#ifndef FENWICK_TREE_H
#define FENWICK_TREE_H

#include <vector>
#include <limits>
#include <algorithm>

template<typename T, bool isReversed = false>
class FenwickTree
{
private:
    const T T_Max = std::numeric_limits<T>::max();
    std::vector<T> tree;
    int size;

    T lowbit(int index) const
    {
        return index & -index;
    }

public:
    FenwickTree(int size);
    FenwickTree(const std::vector<T>& arr, int size);
    
    void init(const std::vector<T>& arr);
    T get(int idx) const;
    void set(int idx, T val, const std::vector<T>& orig_arr);
    T query(int idx);
};

#endif // FENWICK_TREE_H