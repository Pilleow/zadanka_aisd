#include "setasarray.h"
#include <iostream>

#define PRINT(_string) (std::cout << _string << std::endl)

int main() {
    PRINT("Start testu.");

    SetAsArray a = SetAsArray(10);
    SetAsArray b = SetAsArray(10);
    for (int i = 0; i < 10; i += 2) a.Insert(i);
    for (int i = 1; i < 10; i += 2) b.Insert(i);

    PRINT("Wypisuję elementy zbioru A korzystając z iteratora.");

    SetAsArray::Iter a_iter = a.NewIterator();
    while (!a_iter.IsDone()) {
        std::cout << *a_iter << ", ";
        ++a_iter;
    }
    std::cout << std::endl;

    PRINT("Wypisuję elementy zbioru B korzystając z iteratora.");

    SetAsArray::Iter b_iter = b.NewIterator();
    while (!b_iter.IsDone()) {
        std::cout << *b_iter << ", ";
        ++b_iter;
    }
    std::cout << std::endl;

    PRINT("Koniec testu.");
    return 0;
}