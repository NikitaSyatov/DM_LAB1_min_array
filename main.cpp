#include <iostream>

#include "MinFenwickTree.h"
#include "RMQ.h"

int main()
{
    // std::vector<int> arr = {1, 3, 2, 5, 4};
    std::vector<int> arr = {5, 3, 8, 1, 6, 4, 7, 2};

    MinFenwickTree<int> ftree(arr);

    std::cout << ftree.query(2, 6) << std::endl;

    RMQ<int> rmq(arr);

    std::cout << rmq.query(2, 6) << std::endl;

    return 0;
}