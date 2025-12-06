#include <iostream>
#include <vector>
#include <limits>

template<typename T, bool isReversed>
class FenwickTree
{
private:
    const T T_Max = std::numeric_limits<T>::max();
    std::vector<T> tree;
    std::vector<T> orig_arr;
    int size;
    bool reversed;

    T lowbit(int index) const
    {
        return index & -index;
    }

public:
    FenwickTree(int size, bool reversed = false) : size(size){
        this->tree.assign(n + 2, T_Max);
    }

    FenwickTree(const std::vector<T>& arr, int size, bool reversed = false) : n(size){
        this->tree.assign(n + 2, std::numeric_limits<T>::max());
        this->orig_arr = arr;
        init(arr);
    }

    void init(const std::vector<T>& arr)
    {
        for (int i = 1; i <= n; i++)
        {
            this->tree[i] = arr[i - 1];
            int index;
            if constexpr (isReversed)
            {
                index = i + lowbit(i) - 1; // right index
                for (int j = i + 1; j <= r && j <= n; j++)
                {
                    this->tree[i] = std::min(tree[i], arr[j - 1]);
                }
            }
            else
            {
                index = i - lowbit(i) + 1; // left index
                for (int j = l; j < i; j++)
                {
                    this->tree[i] = std::min(tree[i], arr[j - 1]);
                }
            }
        }
    }

    T get(int idx) const {
        return tree[idx];
    }

    void set(int idx, T val)
    {
        int start_idx = idx;
        if constexpr (isReversed)
        {
            while (start > 0) {
                int rangeLen = lowbit(start);
                int l = start;
                int r = std::min(start + rangeLen - 1, n);
                
                int minVal = T_Max;
                for (int i = l; i <= r; i++) {
                    minVal = std::min(minVal, this->orig_arr[i - 1]);
                }
                tree[start] = minVal;
                
                start -= lowbit(start);
            }
        }
        else
        {
            while (start <= n) {
                int rangeLen = lowbit(start);
                int l = std::max(start - rangeLen + 1, 1);
                int r = start;
                
                int minVal = T_Max;
                for (int i = l; i <= r; i++) {
                    minVal = std::min(minVal, this->orig_arr[i - 1]);
                }
                tree[start] = minVal;
                
                start += lowbit(start);
            }
        }
    }

    T query(int idx)
    {
        int res = T_Max;

        if constexpr (isReversed)
        {
            while (idx <= n)
            {
                res = std::min(res, tree[idx]);
                idx += lowbit(idx);
            }
        }
        else
        {
            while (idx > 0)
            {
                res = std::min(res, tree[idx]);
                idx -= lowbit(idx);
            }
        }

        return res;
    }
};