#include <iostream>
#include <vector>
#include <limits>

class FenwickTree
{
private:
    std::vector<int> tree;
    int size;
public:
    FenwickTree(const std::vector<int>& arr, int s, int f)
    {
        size = arr.size();
        tree.resize(size + 1, std::numeric_limits<int>::max());
    }

    void update(int pos, int value)
    {
        pos++;

        while (pos <= size)
        {
            tree[pos] = std::min(tree[pos], value);
            pos += pos & -pos;
        }
    }

    // int query(int index) {
    //     if (index < 0 || index >= n) {
    //         throw out_of_range("Индекс вне границ массива");
    //     }
        
    //     index++;
    //     int min_val = numeric_limits<int>::max();
        
    //     while (index > 0) {
    //         if (tree[index] < min_val) {
    //             min_val = tree[index];
    //         }
    //         index -= index & -index;
    //     }
        
    //     return min_val;
    // }
};