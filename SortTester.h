#ifndef A2S3_SORTTESTER_H
#define A2S3_SORTTESTER_H
#include <iostream>
class SortTester {
public:
    // Расчет времени
    static long long measureTime(void (*sortFunc)(std::vector<int>&, int, int), std::vector<int> arr) {
        auto start = std::chrono::high_resolution_clock::now();
        sortFunc(arr, 0, arr.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }
    // Вывод результатов и запись в файл
    static void testAndPrintResults(void (*sortFunc)(std::vector<int>&, int, int),
                                    const std::string& name,
                                    const std::string& arrayType,
                                    const std::vector<std::vector<int>>& testArrays,
                                    std::ofstream& csvFile) {
        std::cout << "Testing " << name << ":\n";
        for (const auto& arr : testArrays) {
            long long timeTaken = measureTime(sortFunc, arr);
            csvFile << arrayType << "," << name << "," << arr.size() << "," << timeTaken << "\n";
            std::cout << "Size: " << arr.size() << ", Time: " << timeTaken << " ms\n";
        }
        std::cout << "----------------------\n";
    }
};

#endif //A2S3_SORTTESTER_H
