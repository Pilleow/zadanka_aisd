#include <vector>
#include <iostream>
#include <cassert>
#include <stdexcept>
#include <cmath>

using namespace std;

class Container {
protected:

    Container() {};
public:
    virtual unsigned int Count() const = 0;

    virtual bool IsEmpty() const { return Count() == 0; };

    virtual bool IsFull() const = 0;

    virtual void MakeNull() = 0;
};

template<typename T>
class PriorityQueue : public Container {
public:
    virtual void Enqueue(T element) = 0;

    virtual T FindMin() const = 0;

    virtual T DequeueMin() = 0;
};

template<typename T>
class BinaryHeap : public PriorityQueue<T> {
protected:
    int count;
    std::vector<T> data;

public:
    BinaryHeap(unsigned int n);

    BinaryHeap();

    ~BinaryHeap() = default;

    void MakeNull() override;

    void Enqueue(T element) override;

    T FindMin() const override;

    T DequeueMin() override;

    T PeekMin() const;

    bool IsEmpty() const override;

    bool IsFull() const override;

    void Wypisz() const;

    void WypiszMin() const;

    void _heapify(int index);

    unsigned int Count() const override { return count; }
};

template<typename T>
BinaryHeap<T>::BinaryHeap() : count(0) {
    data.reserve(16);
}

template<typename T>
BinaryHeap<T>::BinaryHeap(unsigned int n) : count(0) {
    data.reserve(n);
}

template<typename T>
void BinaryHeap<T>::MakeNull() {
    count = 0;
    data.clear();
}

template<typename T>
void BinaryHeap<T>::Enqueue(T element) {
    std::cout << "DODAJ " << element << endl;
    data.push_back(element);
    int i = count;
    while (i > 0 && data[i] < data[(i - 1) / 2]) {
        swap(data[i], data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    count++;
}

template<typename T>
T BinaryHeap<T>::FindMin() const {
    if (IsEmpty()) throw out_of_range("Kolejka jest pusta.");
    return data[0];
}

template<typename T>
T BinaryHeap<T>::DequeueMin() {
    std::cout << "USUŃ NAJMNIEJSZY" << endl;
    if (IsEmpty()) throw out_of_range("Kolejka jest pusta.");
    T minElement = data[0];
    data[0] = data.back();
    data.pop_back();
    count--;
    _heapify(0);
    return minElement;
}

template<typename T>
T BinaryHeap<T>::PeekMin() const {
    if (IsEmpty()) throw out_of_range("Kolejka jest pusta.");
    return data[0];
}

template<typename T>
void BinaryHeap<T>::_heapify(int i) {
    while (true) {
        int smallest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < count && data[l] < data[smallest]) smallest = l;
        if (r < count && data[r] < data[smallest]) smallest = r;

        if (smallest != i) {
            swap(data[i], data[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
}

template<typename T>
bool BinaryHeap<T>::IsEmpty() const {
    return count == 0;
}

template<typename T>
bool BinaryHeap<T>::IsFull() const {
    // Vector zawsze zwiększa pojemność jeśli jest bliski zapełnienia
    return false;
}

template<typename T>
void BinaryHeap<T>::Wypisz() const {
    int i_space = 1;
    int padding = sizeof(data) / sizeof(int);
    for (int i = 0; i < count; ++i) {
        if (i + 1 == i_space) {
            cout << "\n  ";
            for (int j = 0; j < padding; ++j) cout << " ";
            i_space = (int) pow(2, i_space);
            padding /= 2;
        }
        cout << data[i] << "    ";
    }
    cout << endl;
}

template<typename T>
void BinaryHeap<T>::WypiszMin() const {
    cout << "Najmniejszy element kopca: " << data[0] << "\n" << endl;
}

int main() {
    cout << "Start." << endl;
    for (int n: {10, 2}) {
        BinaryHeap<int> binaryHeap(10);

        cout << "\nTEST DLA binaryHeap(" << n << ");  ----------------------\n" << endl;

        assert(binaryHeap.IsEmpty());
        binaryHeap.Enqueue(5);
        assert(!binaryHeap.IsEmpty());
        binaryHeap.Wypisz();
        binaryHeap.WypiszMin();
        assert(binaryHeap.PeekMin() == 5);
        binaryHeap.Enqueue(6);
        binaryHeap.Wypisz();
        binaryHeap.WypiszMin();
        assert(binaryHeap.PeekMin() == 5);
        binaryHeap.Enqueue(8);
        binaryHeap.Wypisz();
        binaryHeap.WypiszMin();
        assert(binaryHeap.PeekMin() == 5);
        binaryHeap.Enqueue(3);
        binaryHeap.Wypisz();
        binaryHeap.WypiszMin();
        assert(binaryHeap.PeekMin() == 3);
        binaryHeap.Enqueue(9);
        binaryHeap.Wypisz();
        binaryHeap.WypiszMin();
        assert(binaryHeap.PeekMin() == 3);
        binaryHeap.Enqueue(2);
        binaryHeap.Wypisz();
        binaryHeap.WypiszMin();
        assert(binaryHeap.PeekMin() == 2);
        binaryHeap.Enqueue(1);
        binaryHeap.Wypisz();
        binaryHeap.WypiszMin();
        assert(binaryHeap.PeekMin() == 1);
        binaryHeap.DequeueMin();
        binaryHeap.Wypisz();
        binaryHeap.WypiszMin();
        assert(binaryHeap.PeekMin() == 2);
        binaryHeap.DequeueMin();
        binaryHeap.Wypisz();
        binaryHeap.WypiszMin();
        assert(binaryHeap.PeekMin() == 3);
        binaryHeap.MakeNull();
        assert(binaryHeap.IsEmpty());
    }
    cout << "Koniec!" << endl;
    return 0;
}
