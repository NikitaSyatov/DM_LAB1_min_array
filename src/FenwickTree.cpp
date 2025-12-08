#include <iostream>
#include "FenwickTree.h"

template<typename T, bool isReversed>
FenwickTree<T, isReversed>::FenwickTree(int size) : n(size), tree(size + 1, std::numeric_limits<T>::max()) {}

template<typename T, bool isReversed>
void FenwickTree<T, isReversed>::build(const std::vector<T>& arr)
{
    for (int i = 1; i <= n; i++) {
        tree[i] = arr[i - 1];
        if constexpr (!isReversed) {
            // Обычное дерево: tree[i] = min на отрезке [i-lowbit(i)+1, i]
            int range_start = i - lowbit(i) + 1;
            for (int j = range_start; j < i; j++) {
                tree[i] = std::min(tree[i], arr[j - 1]);
            }
        } else {
            // Обратное дерево: tree[i] = min на отрезке [i, i+lowbit(i)-1]
            int range_end = std::min(i + lowbit(i) - 1, n);
            for (int j = i + 1; j <= range_end; j++) {
                tree[i] = std::min(tree[i], arr[j - 1]);
            }
        }
    }
}

template<typename T, bool isReversed>
T FenwickTree<T, isReversed>::get(int idx) const {
    return tree[idx];
}

template<typename T, bool isReversed>
void FenwickTree<T, isReversed>::print() const
{
    std::cout << "[";
    for (int i = 1; i <= n; i++) {
        if (tree[i] == std::numeric_limits<T>::max()) {
            std::cout << "INF";
        } else {
            std::cout << tree[i];
        }
        if (i < n) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

template class FenwickTree<int, true>;
template class FenwickTree<int, false>;
template class FenwickTree<float, true>;
template class FenwickTree<float, false>;
template class FenwickTree<double, true>;
template class FenwickTree<double, false>;
