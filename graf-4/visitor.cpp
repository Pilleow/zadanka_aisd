#include "visitor.h"
#include <iostream>

AddingVisitor::AddingVisitor() : sum(0) {};

void AddingVisitor::Visit(int &element) {
    sum += element;
}

void AddingVisitor::Visit() {
    sum += 1;
}

int AddingVisitor::getAndResetSum() {
    int temp = sum;
    sum = 0;
    return temp;
}

void Odd_Visitor::Visit(int &element) {
    std::cout << "v" << element << ", ";
    if (element % 2 == 1) {
        IsDone_ = true;
        std::cout << " ODD!" << std::endl;
    }
}
