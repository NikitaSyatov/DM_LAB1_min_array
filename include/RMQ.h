#ifndef RMQ_H
#define RMQ_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

template <typename T>
class RMQ {
private:
    std::vector<std::vector<T>> st;  // st[k][i] = min на отрезке [i, i+2^k-1]
    std::vector<int> logs;         // предподсчитанные логарифмы
public:
    RMQ(const std::vector<T>& arr);

    T query(int l, int r);
};

#endif // RMQ_H