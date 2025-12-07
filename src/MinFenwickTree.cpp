#include <iostream>
#include "MinFenwickTree.h"

template<typename T>
MinFenwickTree<T>::MinFenwickTree(const std::vector<T>& arr) : 
        bit(arr.size()), 
        bit_reversed(arr.size()),
        orig_arr(arr),
        size(arr.size())
{
    bit.init(arr);
    bit_reversed.init(arr);
}

template<typename T>
void MinFenwickTree<T>::update(int idx, T val) // 0-indexing
{
    idx++;  // transform 1-indexing

    // Update original array
    this->orig_arr[idx - 1] = val;
    
    // Update tree
    bit.set(idx, val, this->orig_arr);
    bit_reversed.set(idx, val, this->orig_arr);
}

template<typename T>
T MinFenwickTree<T>::query(int l, int r) // 0-indexing
{
    if (l < 0 || r >= size || l > r) {
        return T_Max;
    }
    
    l++; r++; // transform to 1-indexing
    T res = T_Max;

    bit.print();
    bit_reversed.print();

    // move to right
    int i = l;
    while (i <= r) {
        res = std::min(res, bit_reversed.get(i));
        i += lowbit(i);
    }

    i = r;
    while (i >= l) {
        res = std::min(res, bit.get(i));
        i -= lowbit(i);
    }

    T expected = orig_arr[l-1];
    for (int idx = l; idx <= r; idx++) {
        expected = std::min(expected, orig_arr[idx-1]);
    }
    
    if (std::abs(res - expected) > 1e-9) {
        std::cout << "ERROR! Expected: " << expected << "\n";
    }
    
    return res;
}

template class MinFenwickTree<int>;
template class MinFenwickTree<float>;
template class MinFenwickTree<double>;
