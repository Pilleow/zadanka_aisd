#include "setasarray.h"
#include "visitor.h"

#include <iostream>
#include <cassert>

#define PRINT(_string) (std::cout << _string << std::endl)

int main() {
    PRINT("\nTworzę SetAsArray A, B, C, D");
    SetAsArray a = SetAsArray(10);
    SetAsArray b = SetAsArray(10);
    SetAsArray c = SetAsArray(10);
    SetAsArray d = SetAsArray(10);
    PRINT("Wypełniam A, B");
    for (int i = 0; i < 10; i += 2) a.Insert(i);
    for (int i = 1; i < 10; i += 2) b.Insert(i);
    PRINT("Wykonuję C = A + B oraz D = C - B");
    c = a + b;
    d = c - b;
    std::cout << "A = ";
    a.Wypisz();
    std::cout << "B = ";
    b.Wypisz();
    std::cout << "C = ";
    c.Wypisz();
    std::cout << "D = ";
    d.Wypisz();
    PRINT("Przeprowadzam testy operatorów.");
    assert(d == a);
    assert(d <= a);
    assert(!(b == c));
    assert(b <= c);
    a.Insert(1);
    assert(!(d == a));
    assert(d <= a);

    PRINT("\nTest wizytatora.");
    a.Insert(5);
    AddingVisitor visitor_a;
    a.Accept(visitor_a);
    a.Wypisz();
    PRINT("Suma zbioru A = " << visitor_a.getAndResetSum());
    SetAsArray e = SetAsArray(10);
    e = a * b;
    AddingVisitor visitor_e;
    e.Accept(visitor_e);
    e.Wypisz    ();
    PRINT("Suma zbioru E = " << visitor_e.getAndResetSum());
    e.Withdraw(1);
    e.Accept(visitor_e);
    e.Wypisz();
    PRINT("Suma zbioru E = " << visitor_e.getAndResetSum());

    PRINT("\nTest OddVisitora.");
    Odd_Visitor odd_vb;
    b.Wypisz();
    b.Accept(odd_vb);
    PRINT("Czy w B jest nieparzysta:  " << odd_vb.IsDone());
    Odd_Visitor odd_va1;
    a.Wypisz();
    a.Accept(odd_va1);
    PRINT("Czy w A jest nieparzysta:  " << odd_va1.IsDone());
    Odd_Visitor odd_va2;
    a.Withdraw(1);
    a.Withdraw(5);
    a.Wypisz();
    a.Accept(odd_va2);
    PRINT("Czy w A jest nieparzysta:  " << odd_va2.IsDone());


    PRINT("\nSukces!");
    return 0;
}