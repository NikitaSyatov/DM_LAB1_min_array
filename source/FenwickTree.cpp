#include "FenwickTree.h"

template<typename T, bool isReversed>
FenwickTree<T, isReversed>::FenwickTree(int size) : size(size)
{
    this->tree.assign(this->size + 2, T_Max);
}

template<typename T, bool isReversed>
FenwickTree<T, isReversed>::FenwickTree(const std::vector<T>& arr, int size) : size(size)
{
    this->tree.assign(this->size + 2, T_Max);
    init(arr);
}

template<typename T, bool isReversed>
void FenwickTree<T, isReversed>::init(const std::vector<T>& arr)
{
    for (int i = 1; i <= this->size; i++)
    {
        this->tree[i] = arr[i - 1];
        
        if constexpr (isReversed)
        {
            int r = i + lowbit(i) - 1; // right index
            for (int j = i + 1; j <= r && j <= n; j++)
            {
                this->tree[i] = std::min(tree[i], arr[j - 1]);
            }
        }
        else
        {
            int l = i - lowbit(i) + 1; // left index
            for (int j = l; j < i; j++)
            {
                this->tree[i] = std::min(tree[i], arr[j - 1]);
            }
        }
    }
}

template<typename T, bool isReversed>
T FenwickTree<T, isReversed>::get(int idx) const {
    return tree[idx];
}

template<typename T, bool isReversed>
void FenwickTree<T, isReversed>::set(int idx, T val, const std::vector<T>& orig_arr)
{
    if (idx < 1 || idx > this->size) return;
    
    orig_arr[idx - 1] = val;
    
    int start = idx;
    if constexpr (isReversed)
    {
        while (start > 0)
        {
            int rangeLen = lowbit(start);
            int l = start;
            int r = std::min(start + rangeLen - 1, this->size);
            
            T minVal = T_Max;
            for (int i = l; i <= r && i <= this->size; i++) {
                minVal = std::min(minVal, orig_arr[i - 1]);
            }
            tree[start] = minVal;
            
            start -= lowbit(start);
        }
    }
    else
    {
        while (start <= this->size)
        {
            int rangeLen = lowbit(start);
            int l = std::max(start - rangeLen + 1, 1);
            int r = start;
            
            T minVal = T_Max;
            for (int i = l; i <= r; i++) {
                minVal = std::min(minVal, orig_arr[i - 1]);
            }
            this->tree[start] = minVal;
            
            start += lowbit(start);
        }
    }
}

template<typename T, bool isReversed>
T FenwickTree<T, isReversed>::query(int idx)
{
    if constexpr (isReversed)
    {
        if (idx < 1) idx = 1;
        if (idx > this->size) return T_Max;
    }
    else
    {
        if (idx < 1) return T_Max;
        if (idx > this->size) idx = this->size;
    }
    
    T res = T_Max;
    int pos = idx;

    if constexpr (isReversed)
    {
        while (pos <= this->size)
        {
            res = std::min(res, this->tree[pos]);
            pos += lowbit(pos);
        }
    }
    else
    {
        while (pos > 0)
        {
            res = std::min(res, this->tree[pos]);
            pos -= lowbit(pos);
        }
    }

    return res;
}
