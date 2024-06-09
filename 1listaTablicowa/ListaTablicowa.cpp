/*
Zadanie 1 - lista tablicowa
Autor: Igor Zamojski
*/
#include <iostream>
#include <cassert>
#define TABLICA_SIZE 8

using namespace std;

class ListaTablicowa
{
private:
    int lastIndex = 0;
    int tab[TABLICA_SIZE];

public:
    ListaTablicowa() {}

    /**
     * Wypisuje listę na stdout, format [1, 2, 3, ..., n]
     */
    void printList()
    {
        cout << "[";
        for (int i = 0; i < lastIndex; i++)
        {
            cout << tab[i] << ", ";
        }
        cout << "]" << endl;
    }

    /**
     * Zwraca pozycję elementu pierwszego
     */
    int First()
    {
        if (lastIndex == 0)
            return -1;
        return 0;
    };

    /**
     * Zwraca pozycję za ostatnim elementem
     */
    int End()
    {
        return lastIndex;
    };

    /**
     * Zwraca indeks następnego elementu po p
     * Jeżeli nie istnieje taki element, zwraca -1
     */
    int Next(int p)
    {
        if (p < lastIndex)
            return p + 1;
        return -1;
    };

    /**
     * Zwraca indeks poprzedniego elementu przed p
     * Jeżeli nie istnieje taki element, zwraca -1
     */
    int Previous(int p)
    {
        if (p > 0)
            return p - 1;
        else
            return -1;
    };

    /**
     * Wstawia x do komórki o indeksie p.
     * Zwraca true jeżeli operacja się powiodła
     * i false w przeciwnym wypadku.
     */
    bool Insert(int x, int p)
    {
        if (p > lastIndex) p = lastIndex;
        if (p < 0 || p >= TABLICA_SIZE)
        {
            return false;
        }

        // przesuwamy elementy do przodu aby
        // zrobić miejsce i potem wstawiamy
        for (int i = lastIndex - 1; i >= p; --i)
        {
            tab[i + 1] = tab[i];
        }
        tab[p] = x;
        lastIndex++;

        return true;
    };

    /**
     * Usuwa element na indeksie p.
     * Zwraca true jeżeli operacja się powiodła
     * i false w przeciwnym wypadku.
     */
    bool Delete(int p)
    {
        if (p > lastIndex) p = lastIndex;
        else if (p < 0)
        {
            return false;
        }

        // przesuwamy wszyskie elementy do tyłu
        // tym samym zastępując element który usuwamy
        for (int i = p; i < lastIndex; ++i)
        {
            tab[i] = tab[i + 1];
        }
        lastIndex--;

        return true;
    }

    /**
     * Zwraca pozycję elementu x w liście.
     * Jeżeli nie istnieje, zwraca wartość -1.
     */
    int Locate(int x)
    {
        for (int i = 0; i < lastIndex; ++i)
        {
            if (tab[i] == x)
                return i;
        }
        return -1;
    }

    /**
     * zwraca element znajdujący się w liście w komórce o indeksie p, jeśli
     * pozycja p jest poprawna - wpp zwraca INT_MIN.
     */
    int Retrieve(int p)
    {
        if (p < 0 || p >= lastIndex)
            return INT_MIN;
        return tab[p];
    }
};

int main(int argc, char const *argv[]) // main służy wyłącznie do testów, niczego nie wyświetla
{
    ListaTablicowa lt = ListaTablicowa();

    // czy First i End sie zgadzaja?
    assert(lt.First() == -1);
    assert(lt.End() == 0);

    // wrzucamy 6 elementów, nowy First = 0, nowy End = 6 (bo indeksy 0-5 zajęte)
    assert (lt.Insert(1, 0) == true);
    lt.Insert(2, 0);
    lt.Insert(3, 0);
    lt.Insert(4, 0);
    lt.Insert(5, 0);
    lt.Insert(6, 0);
    assert(lt.First() == 0);
    assert(lt.End() == 6);

    // przepełniamy, sprawdzamy czy Insert == false, następnie wracamy do poprzedniego stanu
    assert (lt.Insert(6, 6) == true);
    assert (lt.Insert(7, 7) == true);
    assert (lt.Insert(8, 8) == false); // przepełnienie!
    assert (lt.Delete(lt.End() - 1) == true); // usuwamy 6
    assert (lt.Delete(lt.End() - 1) == true); // usuwamy 7

    // czy Retrieve dobrze zwraca INT_MIN?
    assert (lt.Retrieve(INT_MAX) == INT_MIN);

    // wkladamy nowy element w srodek
    lt.Insert(99, 3);
    assert(lt.Locate(1) == 6); // bo przesunęliśmy wszystkie elementy na prawo od 99 o 1 w prawo
    assert(lt.Locate(99) == 3);
    assert(lt.Retrieve(3) == 99);

    // usuwamy 99
    lt.Delete(3);
    assert(lt.Locate(1) == 5); // bo przesunęliśmy wszystkie elementy na prawo od 99 o 1 w lewo
    assert(lt.Locate(99) == -1);

    // usuwamy wszystkie elementy, na koniec pusta lista
    assert (lt.Delete(0) == true);
    lt.Delete(0);
    lt.Delete(0);
    lt.Delete(0);
    lt.Delete(0);
    lt.Delete(0);
    assert(lt.First() == -1);
    assert(lt.End() == 0);

    cout << "Wszystkie testy powiodły się :)" << endl;

    return 0;
}
