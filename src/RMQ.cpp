#include "RMQ.h"

template <typename T>
RMQ<T>::RMQ(const std::vector<T>& arr)
{
    int n = arr.size();
    int K = (int)log2(n) + 1;
    
    st.resize(K, std::vector<T>(n));
    
    for (int i = 0; i < n; i++) {
        st[0][i] = arr[i];
    }
    
    for (int k = 1; k < K; k++) {
        int shift = 1 << (k - 1);  // 2^(k-1)
        for (int i = 0; i + (1 << k) <= n; i++) {
            st[k][i] = std::min(st[k-1][i], st[k-1][i + shift]);
        }
    }
    
    this->logs.resize(n + 1);
    this->logs[1] = 0;
    for (int i = 2; i <= n; i++) {
        this->logs[i] = this->logs[i/2] + 1;
    }
}

template <typename T>
T RMQ<T>::query(int l, int r)
{
    int length = r - l + 1;
    int k = this->logs[length];
    return std::min(this->st[k][l], st[k][r - (1 << k) + 1]);
}

template class RMQ<int>;
template class RMQ<float>;
template class RMQ<double>;
