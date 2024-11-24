#ifndef A2S3_ARRAYGENERATOR_H
#define A2S3_ARRAYGENERATOR_H
#include <iostream>
#include <random>
class ArrayGenerator {
public:
    // Создание случайного массива
    static std::vector<int> generateRandomArray(int size, int range_start, int range_end) {
        std::vector<int> arr(size);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(range_start, range_end);
        for (int& num : arr) {
            num = dis(gen);
        }
        return arr;
    }
    // Создание обратно отсортированного массива
    static std::vector<int> generateReverseSortedArray(int size) {
        std::vector<int> arr(size);
        for (int i = 0; i < size; ++i) {
            arr[i] = size - i;
        }
        return arr;
    }
    // Создание почти отсортированного массива
    static std::vector<int> generateAlmostSortedArray(int size, int swaps) {
        std::vector<int> arr(size);
        for (int i = 0; i < size; ++i) {
            arr[i] = i + 1;
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        for (int i = 0; i < swaps; ++i) {
            int idx1 = gen() % size;
            int idx2 = gen() % size;
            std::swap(arr[idx1], arr[idx2]);
        }
        return arr;
    }
};

#endif //A2S3_ARRAYGENERATOR_H
