#include <vector>
#include <fstream>
#include "SortTester.h"
#include "ArrayGenerator.h"

void insertionSort(std::vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1);
    std::vector<int> R(n2);
    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int i = 0; i < n2; ++i) R[i] = arr[mid + 1 + i];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}
//Гибридная merge+insertion сортировка
void hybridMergeSort(std::vector<int>& arr, int left, int right) {
    if (right - left + 1 <= 15) {
        insertionSort(arr, left, right);
        return;
    }
    int mid = left + (right - left) / 2;
    hybridMergeSort(arr, left, mid);
    hybridMergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Обычная merge сортировка
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}
int main() {
    std::ofstream dataFile("../result15.csv");
    dataFile << "ArrayType,SortType,Size,Time\n";
    int max_size = 10000;
    std::vector<int> randomArray = ArrayGenerator::generateRandomArray(max_size, 0, 6000);
    std::vector<int> reverseSortedArray = ArrayGenerator::generateReverseSortedArray(max_size);
    std::vector<int> almostSortedArray = ArrayGenerator::generateAlmostSortedArray(max_size, 1000);
    std::vector<std::vector<int>> randomTestArrays;
    for (int i = 500; i < 10000; i += 100) {
        randomTestArrays.emplace_back(randomArray.begin(), randomArray.begin() + i);
    }
    std::vector<std::vector<int>> reverseTestArrays;
    for (int i = 500; i < 10000; i += 100) {
        reverseTestArrays.emplace_back(reverseSortedArray.begin(), reverseSortedArray.begin() + i);
    }
    std::vector<std::vector<int>> almostSortedTestArrays;
    for (int i = 500; i < 10000; i += 100) {
        almostSortedTestArrays.emplace_back(almostSortedArray.begin(), almostSortedArray.begin() + i);
    }
    std::cout << "----------------------\n";
    std::cout << "Testing random arrays" << "\n" << "----------------------" <<"\n";
    SortTester::testAndPrintResults(mergeSort, "Standard Merge Sort", "Random", randomTestArrays, dataFile);
    SortTester::testAndPrintResults(hybridMergeSort, "Hybrid Merge Sort", "Random", randomTestArrays, dataFile);
    std::cout << "----------------------\n";
    std::cout << "Testing reverse sorted arrays" << "\n" << "------------------------" <<"\n";
    SortTester::testAndPrintResults(mergeSort, "Standard Merge Sort", "Reverse", reverseTestArrays, dataFile);
    SortTester::testAndPrintResults(hybridMergeSort, "Hybrid Merge Sort", "Reverse",reverseTestArrays, dataFile);
    std::cout << "----------------------\n";
    std::cout << "Testing almost sorted arrays" << "\n" << "------------------------" <<"\n";
    SortTester::testAndPrintResults(mergeSort, "Standard Merge Sort", "AlmostSorted", almostSortedTestArrays, dataFile);
    SortTester::testAndPrintResults(hybridMergeSort, "Hybrid Merge Sort", "AlmostSorted", almostSortedTestArrays, dataFile);

    return 0;
}
