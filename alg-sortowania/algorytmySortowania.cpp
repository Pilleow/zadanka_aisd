#include <iostream>
#include <vector>

void insertionSort(std::vector<int>& array) {
    int n = array.size();

    for (int i = 1; i < n; ++i) {
        int key = array[i];
        int j = i - 1;

        // Przesuwanie elementów większych od klucza o jedno miejsce w prawo
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            --j;
        }

        // Wstawienie klucza na odpowiednie miejsce
        array[j + 1] = key;
    }
}

void selectionSort(std::vector<int>& array) {
    int n = array.size();

    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;

        for (int j = i + 1; j < n; ++j) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }

        // Zamiana elementów
        std::swap(array[i], array[minIndex]);
    }
}

void bubbleSort(std::vector<int>& array) {
    int n = array.size();

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (array[j] > array[j + 1]) {
                // Zamiana elementów
                std::swap(array[j], array[j + 1]);
            }
        }
    }
}

void quickSort(std::vector<int>& array, int low, int high) {
    if (low < high) {
        std::vector<int> &array1 = array;
        int pivot = array1[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; ++j) {
            if (array1[j] < pivot) {
                ++i;
                std::swap(array1[i], array1[j]);
            }
        }

        std::swap(array1[i + 1], array1[high]);
        int pivotIndex = i + 1;

        quickSort(array, low, pivotIndex - 1);
        quickSort(array, pivotIndex + 1, high);
    }
}

int main() {
    std::vector<int> array1 = {12, 11, 13, 5, 6};
    insertionSort(array1);
    std::cout << "Posortowana tablica (INSERTION SORT): ";
    for (const auto& element : array1) {
        std::cout << element << " ";
    }

    std::vector<int> array2 = {64, 25, 12, 22, 11};
    selectionSort(array2);

    std::cout << "Posortowana tablica (SELECTION SORT): ";
    for (const auto& element : array2) {
        std::cout << element << " ";
    }

    std::vector<int> array3 = {64, 34, 25, 12, 22, 11, 90};
    bubbleSort(array3);

    std::cout << "Posortowana tablica (BUBBLE SORT): ";
    for (const auto& element : array3) {
        std::cout << element << " ";
    }

    std::vector<int> array4 = {10, 7, 8, 9, 1, 5};
    quickSort(array4, 0, array4.size() - 1);

    std::cout << "Posortowana tablica (QUICK SORT): ";
    for (const auto& element : array4) {
        std::cout << element << " ";
    }

    return 0;
}
