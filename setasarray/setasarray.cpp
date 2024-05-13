#include "setasarray.h"
#include <algorithm>
#include <iostream>
#include <cassert>

SetAsArray::SetAsArray(unsigned int n) : Set(n), array(n, false) {
    count = 0;
}

void SetAsArray::MakeNull() {
    array = std::vector(universeSize, false);
    count = 0;
}

void SetAsArray::Insert(int element) {
    if (array[element]) return;
    array[element] = true;
    count++;
}

bool SetAsArray::IsMember(int element) const {
    return array[element];
}

void SetAsArray::Withdraw(int element) {
    if (!array[element]) return;
    array[element] = false;
    count--;
}

void SetAsArray::Accept(Visitor<int> &v) {
    for (int i = 0; i < universeSize; ++i) {
        if (v.IsDone()) break;
        if (array[i]) v.Visit(i);
    }
}

SetAsArray operator+(const SetAsArray &a1, const SetAsArray &a2) {
    SetAsArray larger = a1;
    SetAsArray smaller = a2;
    if (a1.universeSize < a2.universeSize) {
        smaller = a1;
        larger = a2;
    }

    SetAsArray out = SetAsArray(larger.universeSize);
    // następne trzy linijki można zrefaktoryzować do metody copy(...)
    std::copy(larger.array.begin(), larger.array.end(), out.array.begin());
    out.count = larger.count;
    out.universeSize = larger.universeSize;
    for (int i = 0; i < sizeof(smaller.array) / sizeof(int); ++i) out.array[i] = out.array[i] || smaller.array[i];
    return out;
}

SetAsArray operator-(const SetAsArray &a1, const SetAsArray &a2) {
    SetAsArray larger = a1;
    SetAsArray smaller = a2;
    if (a1.universeSize < a2.universeSize) {
        smaller = a1;
        larger = a2;
    }

    SetAsArray out = SetAsArray(larger.universeSize);
    // następne trzy linijki można zrefaktoryzować do metody copy(...)
    std::copy(larger.array.begin(), larger.array.end(), out.array.begin());
    out.count = larger.count;
    out.universeSize = larger.universeSize;
    for (int i = 0; i < sizeof(smaller.array) / sizeof(int); ++i) out.array[i] = out.array[i] && !smaller.array[i];
    return out;
}

SetAsArray operator*(const SetAsArray &a1, const SetAsArray &a2) {
    SetAsArray larger = a1;
    SetAsArray smaller = a2;
    if (a1.universeSize < a2.universeSize) {
        smaller = a1;
        larger = a2;
    }
    SetAsArray out = SetAsArray(larger.universeSize);
    // następne trzy linijki można zrefaktoryzować do metody copy(...)
    std::copy(larger.array.begin(), larger.array.end(), out.array.begin());
    out.count = larger.count;
    out.universeSize = larger.universeSize;
    for (int i = 0; i < sizeof(smaller.array) / sizeof(int); ++i) out.array[i] = out.array[i] && smaller.array[i];
    return out;
}

bool operator==(const SetAsArray &a1, const SetAsArray &a2) {
    if (a1.count != a2.count) return false;
    return a1.array == a2.array;
}

bool operator<=(const SetAsArray &a1, const SetAsArray &a2) {
    if (a1.count > a2.count) return false;
    for (int i = 0; i < sizeof(a1.array) / sizeof(int); ++i) if (a1.array[i] && !a2.array[i]) return false;
    return true;
}

void SetAsArray::Wypisz() const {
    std::cout << "{";
    for (int i = 0; i < universeSize; ++i) {
        if (array[i]) {
            std::cout << i << ", ";
        }
    }
    std::cout << "}" << std::endl;
}
