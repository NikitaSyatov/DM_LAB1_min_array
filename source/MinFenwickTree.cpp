#include "MinFenwickTree.h"

template<typename T>
MinFenwickTree<T>::MinFenwickTree(const std::vector<int>& arr) : 
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
    
    // update original array
    this->orig_arr[idx - 1] = val;
    
    // Update tree
    bit1.update(idx, val, this->orig_arr);
    bit2.update(idx, val, this->orig_arr);
}

template<typename T>
T MinFenwickTree<T>::query(int l, int r) // 0-indexing
{
    l++; r++; // transform to 1-indexing
    T res = T_Max;

    // move to right
    while (i + lowbit(i) - 1 <= r) {
        res = std::min(res, bit_reversed.get(i));
        i += lowbit(i);
    }
    
    // move to left
    i = r;
    while (i - lowbit(i) + 1 >= l) {
        res = std::min(res, bit.get(i));
        i -= lowbit(i);
    }
    
    // last elem
    if (i >= l && i <= r) {
        res = std::min(res, original[i - 1]);
    }
    
    return res;
}
