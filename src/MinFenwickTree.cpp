#include <iostream>
#include "MinFenwickTree.h"

template<typename T>
MinFenwickTree<T>::MinFenwickTree(const std::vector<T>& input) 
        : arr(input), 
          n(static_cast<int>(input.size())),
          forwardTree(input.size()),
          backwardTree(input.size())
{     
    if (n == 0) return;
    
    // Построение деревьев
    forwardTree.build(arr);
    backwardTree.build(arr);
    
    // Для отладки выведем деревья
    std::cout << "Forward Tree: ";
    forwardTree.print();
    std::cout << "Backward Tree: ";
    backwardTree.print();
}

template<typename T>
T MinFenwickTree<T>::query(int l, int r) // 0-indexing
{
    if (l < 0 || r >= n || l > r)
    {
        return std::numeric_limits<T>::max();
    }
        
    // Преобразуем к 1-indexed
    l++; r++;
    
    T result = std::numeric_limits<T>::max();
    
    // Основная идея:
    // 1. Используем обратное дерево для движения вправо от l
    // 2. Используем прямое дерево для движения влево от r
    
    // Движение вправо от l (используем обратное дерево)
    int i = l;
    while (i <= r) {
        int block_end = std::min(i + lowbit(i) - 1, n);
        if (block_end <= r) {
            // Весь блок внутри [l, r]
            result = std::min(result, backwardTree.get(i));
            i = block_end + 1;
        } else {
            // Блок выходит за правую границу
            result = std::min(result, arr[i - 1]);
            i++;
        }
    }
        
    // Движение влево от r (используем прямое дерево)
    i = r;
    while (i >= l) {
        int block_start = i - lowbit(i) + 1;
        if (block_start >= l) {
            // Весь блок внутри [l, r]
            result = std::min(result, forwardTree.get(i));
            i = block_start - 1;
        } else {
            // Блок выходит за левую границу
            result = std::min(result, arr[i - 1]);
            i--;
        }
    }
    
    return result;
}
    

template class MinFenwickTree<int>;
template class MinFenwickTree<float>;
template class MinFenwickTree<double>;
