#include <iostream>
#include <vector>

#define print(s) (cout << endl << s << endl)


void print_array(const int *arr, int N);

using namespace std;

void rebuild_heap(int arr[], int N, int i) {
    // poniższe integery (smallest, l, r) pochodzą
    // bezpośrednio z tablicowej postaci kopca!
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    // teraz przesuwamy tak, aby największy był jako root
    if (l < N && arr[l] < arr[smallest]) smallest = l;
    if (r < N && arr[r] < arr[smallest]) smallest = r;
    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        // na koniec rekurencyjnie sortujemy kolejne poddrzewa
        // ale tylko jeśli zmienił się ich korzeń (jesteśmy w if!)
        rebuild_heap(arr, N, smallest);
    }
}

void heap_sort(int arr[], int N) {
    // tworzymy kopiec z aktualnej tablicy
    // (kopiec jest drzewem w formie tablicy)
    for (int i = N / 2 - 1; i >= 0; --i) {
        rebuild_heap(arr, N, i);
    }

    // i teraz wyciągamy najmniejszy element i naprawiamy kopiec
    for (int i = N - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        rebuild_heap(arr, i, 0);
    }
}

int main() {
    int arr[] = {1, 9, 16, 27, 35, 42, 51, 68, 79, 86, 94, 2, 11, 18, 29, 37, 44, 53, 70, 81, 88, 96, 3, 12, 20, 31, 39, 46, 55, 72, 83, 90, 98, 4, 13, 21, 32, 40, 47, 56, 73, 84, 91, 99, 5, 14, 22, 33, 41, 48, 57, 74, 85, 92, 100, 6, 15, 23, 34, 43, 50, 59, 76, 87, 95, 7, 16, 24, 35, 42, 51, 60, 77, 88, 97, 8, 17, 25, 36, 44, 53, 62, 79, 90, 98, 10, 19, 26, 37, 45, 54, 63, 80, 91, 99};
    int N = sizeof(arr) / sizeof(int);

    print("Tablica przed sortowaniem(sizeof(arr) = " << sizeof(arr)/sizeof(int) << "):");
    print_array(arr, N);
    heap_sort(arr, N);
    print("Tablica po sortowaniu (sizeof(arr) = " << sizeof(arr)/sizeof(int) << "):");
    print_array(arr, N);
    return 0;
}

void print_array(const int *arr, int N) {
    for (int i = 0; i < N; ++i) {
        cout << arr[i];
        if (i != N - 1) cout << ", ";
    }
}
