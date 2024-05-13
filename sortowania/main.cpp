#include <iostream>
#include <algorithm>
#include <random>


void printArr(const int *arr, int n);

void bubbleSort(int *arr, int n);
void selectionSort(int *arr, int n);
void insertionSort(int *arr, int n);
void quickSort(int *arr, int low, int high);
int partition(int *arr, int low, int high);

void heapSort(int *arr, int n);

using namespace std;

int main() {
    random_device rd;
    default_random_engine rng(rd());

    int arr[] = {15, 8, 3, 2, 11, 14, 6, 4, 7, 1, 9, 20, 17, 10, 18, 12, 19, 13, 5, 16};
    int n = sizeof(arr) / sizeof(arr[0]);

    shuffle(arr, arr + n, rng);
    cout << "Przed Bubble Sort" << endl;
    printArr(arr, n);
    bubbleSort(arr, n);
    cout << "Po Bubble Sort" << endl;
    printArr(arr, n);

    cout << endl;
    shuffle(arr, arr + n, rng);

    cout << "Przed Selection Sort" << endl;
    printArr(arr, n);
    selectionSort(arr, n);
    cout << "Po Selection Sort" << endl;
    printArr(arr, n);

    cout << endl;
    shuffle(arr, arr + n, rng);

    cout << "Przed Insertion Sort" << endl;
    printArr(arr, n);
    insertionSort(arr, n);
    cout << "Po Insertion Sort" << endl;
    printArr(arr, n);

    cout << endl;
    shuffle(arr, arr + n, rng);

    cout << "Przed Quick Sort" << endl;
    printArr(arr, n);
    quickSort(arr, 0, n - 1);
    cout << "Po Quick Sort" << endl;
    printArr(arr, n);

    cout << endl;
    shuffle(arr, arr + n, rng);

    cout << "Przed Heap Sort" << endl;
    printArr(arr, n);
    heapSort(arr, n);
    cout << "Po Heap Sort" << endl;
    printArr(arr, n);

    return 0;
}

void heapify( int *arr, int n, int i ) {
    int largest_idx = i;
    int left_idx = 2 * i + 1;
    int right_idx = 2 * i + 2;

    if (left_idx < n && arr[largest_idx] < arr[left_idx]) largest_idx = left_idx;
    if (right_idx < n && arr[largest_idx] < arr[right_idx]) largest_idx = right_idx;

    if (largest_idx == i) return;
    swap(arr[largest_idx], arr[i]);
    heapify(arr, n, largest_idx);
}

void heapSort( int *arr, int n ) {
    for (int i = n / 2 - 1; i >= 0; --i) heapify(arr, n, i);
    for (int i = n - 1; i >= 0; --i) {
        swap(arr[i], arr[0]);
        heapify(arr, i, 0);
    }
}

void quickSort(int *arr, int low, int high) {
    if (low >= high) return;

    int i, j, pivot;
    pivot = arr[high];
    i = low - 1;
    for (j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[j], arr[i]);
        }
    }

    int split_id = i + 1;
    swap(arr[split_id], arr[high]);
    quickSort(arr, low, split_id - 1);
    quickSort(arr, split_id + 1, high);
}

void insertionSort(int *arr, int n) {
    int i, j;
    for (i = 0; i < n - 1; ++i) {
        j = i;
        while (arr[j] > arr[j + 1]) {
            swap(arr[j], arr[j + 1]);
            j--;
        }
    }
}

void selectionSort(int *arr, int n) {
    int i, j, min_idx;
    for (i = 0; i < n - 1; ++i) {
        min_idx = i + 1;
        for (j = i; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr[i], arr[min_idx]);
    }
}

void bubbleSort(int *arr, int n) {
    int i;
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (i = 0; i < n - 1; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
    }
}

void printArr(const int *arr, int n) {
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << ' ';
    }
    cout << endl;
}
