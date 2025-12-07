#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
#include <limits>
#include <sstream>
#include <algorithm>
#include <cstring>

#include "MinFenwickTree.h"
#include "RMQ.h"

void userMode(std::ofstream& outFile) {
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "Print array (elements, delimeter - space)" << std::endl;

    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    std::vector<double> arr;
    double value;

    while (ss >> value) {
        arr.push_back(value);
    }
    
    if (arr.empty()) {
        std::cout << "ERROR | Array is empty!\n";
        return;
    }

    std::cout << "Your array:" << std::endl;
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i];
        if (i < arr.size() - 1) std::cout << ", ";
    }
    std::cout << "\n\n";
    
    // Создание структур данных
    MinFenwickTree<double> ftree(arr);
    RMQ<double> rmq(arr);
    
    std::cout << "=== USER MODE ===\n";
    
    while (true) {
        int l, r;
        std::cout << "Add range for query: [l r]: (-1 -1 is exit)" << std::endl;
        
        if (!(std::cin >> l >> r)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода! Пожалуйста, введите два числа.\n";
            continue;
        }
        
        if (l == -1 || r == -1) {
            std::cout << "Exit.\n";
            break;
        }
        
        if (l < 0 || r >= static_cast<int>(arr.size()) || l > r) {
            std::cout << "ERROR | uncorrect range! Max range: [0, " 
                      << arr.size() - 1 << "], l <= r\n";
            continue;
        }

        double ftreeResult = ftree.query(l, r);
        double rmqResult = rmq.query(l, r);
        
        std::cout << std::fixed << std::setprecision(6);
        std::cout << "Query: [" << l << ", " << r << "]:\n";
        std::cout << "  MinFenwickTree: " << ftreeResult << "\n";
        std::cout << "  RMQ: " << rmqResult << "\n";
        
        if (std::abs(ftreeResult - rmqResult) < 1e-9) {
            std::cout << "Results are the same\n\n";
        } else {
            std::cout << "ERROR | Results is different! Difference:" 
                      << std::abs(ftreeResult - rmqResult) << "\n\n";
        }
    }
}

void autoMode(std::ofstream& outFile)
{
    std::cout << "=== AUTO MODE ===\n";
    
    int N, step, struct_mode;
    
    while (true) {
        std::cout << "Enter Max length array (min = 10) (N > 0): ";
        if (!(std::cin >> N)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "ERROR | N must be integer!\n";
            continue;
        }
        
        if (N <= 0) {
            std::cout << "ERROR | N < 0!\n";
            continue;
        }
        break;
    }
    
    while (true) {
        std::cout << "Enter step for iteration: (1 <= step <= " << N << "): ";
        if (!(std::cin >> step)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "ERROR | step must be integer!\n";
            continue;
        }
        
        if (step <= 0 || step > N) {
            std::cout << "ERROR | step must be in range: [1, " << N << "]!\n";
            continue;
        }
        break;
    }

    std::cout << "Choose mode: (1 - Fenwick, 2 - RMQ)" << std::endl;
    std::cin >> struct_mode;
    
    std::cout << "Max length array: " << N << "\n";
    std::cout << "Iteration step: " << step << "\n\n";
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 1000.0);
    
    std::cout << std::fixed << std::setprecision(6);
    outFile << std::fixed << std::setprecision(6);
    
    std::cout << "\n" << std::string(80, '-') << "\n";
    std::cout << std::setw(10) << "Size" 
              << std::setw(15) << "Time" << "\n";
    std::cout << std::string(80, '-') << "\n";
    
    for (int size = step; size <= N; size += step) {
        std::vector<double> arr(size);
        for (int i = 0; i < size; ++i) {
            arr[i] = dist(gen);
        }
        
        std::uniform_int_distribution<int> idxDist(0, size - 1);
        int l = idxDist(gen);
        int r = idxDist(gen);
        if (l > r) std::swap(l, r);

        double ftreeResult;
        double rmqResult;

        if (struct_mode == 1)
        {
            auto start = std::chrono::high_resolution_clock::now();
            MinFenwickTree<double> ftree(arr);
            double ftreeResult = ftree.query(l, r);
            RMQ<double> rmq(arr);
            double rmqResult = rmq.query(l, r);
            auto End = std::chrono::high_resolution_clock::now();
            auto Time = std::chrono::duration_cast<std::chrono::microseconds>(End - start).count();
            
            std::cout << std::setw(10) << size 
                  << std::setw(15) << Time << "\n";
            outFile << std::setw(10) << size 
                    << std::setw(15) << Time << "\n";
        }
        else if (struct_mode == 2)
        {
            auto start = std::chrono::high_resolution_clock::now();
            MinFenwickTree<double> ftree(arr);
            double ftreeResult = ftree.query(l, r);
            RMQ<double> rmq(arr);
            double rmqResult = rmq.query(l, r);
            auto rmqEnd = std::chrono::high_resolution_clock::now();
            auto Time = std::chrono::duration_cast<std::chrono::microseconds>(rmqEnd - start).count();
        
            std::cout << std::setw(10) << size 
                  << std::setw(15) << Time << "\n";
            outFile << std::setw(10) << size 
                    << std::setw(15) << Time << "\n";
        }
        else
        {
            std::cout << "ERROR | uncorrect struct mode: struct mode is 1(Fenwick) or 2(RMQ)" << std::endl;
        }
        bool resultsMatch = std::abs(ftreeResult - rmqResult) < 1e-9;
        double difference = std::abs(ftreeResult - rmqResult);
        
        if (!resultsMatch) {
            std::cerr << "  ERROR | Results is different! Query: [" << l << ", " << r << "], "
                    << "FT=" << ftreeResult << ", RMQ=" << rmqResult << "\n";
        }
    }

    std::cout << "exit.";
}

void printHelp(const char* programName) {
    std::cout << "Usage: " << programName << " <MODE>\n\n";
    std::cout << "Modes:\n";
    std::cout << "  -u, --user\t\tUser input\n";
    std::cout << "  -a, --auto\tAuto input (test complexity)\n";
    std::cout << "  -h, --help\t\tPrint this usage\n\n";
}

int main(int argc, char* argv[]) {
    std::ofstream outFile("results.txt", std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "ERROR | File results.txt does not exist\n";
        return 1;
    }
    
    if (argc != 2) {
        std::cerr << "ERROR | Uncorrect mode\n\n";
        printHelp(argv[0]);
        outFile.close();
        return 1;
    }
    char* mode = argv[1];
    
    if (strcmp(mode, "-h") == 0) {
        printHelp(argv[0]);
    }
    else if (strcmp(mode, "-u") == 0) {
        userMode(outFile);
    }
    else if (strcmp(mode, "-a") == 0) {
        autoMode(outFile);
    }
    else {
        std::cerr << "ERROR | undefined mode '" << mode << "'!\n\n";
        printHelp(argv[0]);
        outFile.close();
        return 1;
    }
    
    outFile.close();
    
    return 0;
}