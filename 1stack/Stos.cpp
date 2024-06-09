/*
Zadanie 4 - stos
Autor: Igor Zamojski
*/
#include <iostream>

#define TABLICA_SIZE 32
#define PRINTSP(s) (std::cout << std::endl \
                              << s << std::endl)

// LISTA WSKAŹNIKOWA  ------------------------------------------------------------------------------------- //

template <typename element>
struct cellJedn
{
    element data;
    cellJedn *next;

    cellJedn(element value) : data(value), next(nullptr) {}
};

template <typename element>
class ListaJednokierunkowa
{
protected:
    /* głowa listy */
    cellJedn<element> *header;

public:
    /*
    konstruktor
    tworzymy głowę listy
    */
    ListaJednokierunkowa() : header(nullptr) {}
    /*
    destruktor
    usuwamy wszystkie elementy (zwalniamy miejsce)
    */
    ~ListaJednokierunkowa()
    {
        while (header)
        {
            cellJedn<element> *temp = header;
            header = header->next;
            delete temp;
        }
    }

    /*
    wstawia element x na pozycję next komórki o wskaźniku p
    (lub w przypadku pustej listy tworzy komórkę z elementem x w miejscu głowy listy)
    */
    void Insert(element x, cellJedn<element> *p)
    {
        cellJedn<element> *newCell = new cellJedn<element>(x);

        if (p == nullptr)
        { // wstawiamy na początek listy
            newCell->next = header;
            header = newCell;
        }
        else
        { // wstawiamy za wskazaną komórkę
            newCell->next = p->next;
            p->next = newCell;
        }
    }

    /*
    usuwa komórkę z pozycji next komórki o wskaźniku p i zwraca true
    zwraca false, gdy usunięcie nie jest możliwe
    */
    bool Delete(cellJedn<element> *p)
    {
        if (p == nullptr || header == nullptr)
            return false;
        cellJedn<element> *prev = Previous(p);
        if (prev)
            prev->next = p->next;
        else
            header = p->next;
        delete p;
        return true;
    }

    /*
    zwraca element komórki o wskaźniku p
    zwraca pustą wartość dla p = nullptr
    */
    element Retrieve(cellJedn<element> *p)
    {
        return p != nullptr ? p->data : element();
    }

    /*
    zwraca wskaźnik do pierwszej komórki z elementem x
    */
    cellJedn<element> *Locate(element x)
    {
        cellJedn<element> *current = header;
        while (current != nullptr && current->data != x)
            current = current->next;
        return current;
    }

    /*
    zwraca wskaźnik do pierwszej komórki na liście
    */
    cellJedn<element> *First()
    {
        return header;
    }

    /*
    zwraca wskaźnik do kolejnej komórki po komórce o wskaźniku p
    zwraca nullptr dla p = nullptr
    */
    cellJedn<element> *Next(cellJedn<element> *p)
    {
        return p != nullptr ? p->next : nullptr;
    }

    /*
    zwraca wskaźnik do komórki poprzedzającej komórkę o wskaźniku p
    zwraca nullptr dla p = nullptr
    */
    cellJedn<element> *Previous(cellJedn<element> *p)
    {
        cellJedn<element> *current = header;
        while (current != nullptr && current->next != p)
            current = current->next;
        return current;
    }

    /*
    zwraca wskaźnik do ostatniej komórki na liście
    */
    cellJedn<element> *Last()
    {
        cellJedn<element> *current = header;
        while (current != nullptr && current->next != nullptr)
            current = current->next;
        return current;
    }

    /*
    wyświetla wszystkie elementy listy
    */
    void print()
    {
        cellJedn<element> *current = header;
        std::cout << "[";
        while (current != nullptr)
        {
            std::cout << current->data;
            if (current->next != nullptr)
                std::cout << ", ";
            current = current->next;
        }
        std::cout << "]" << std::endl;
    }
};

// LISTA TABLICOWA  ------------------------------------------------------------------------------------- //

template <typename element>
class ListaTablicowa
{
protected:
    int lastIndex = 0;
    element tab[TABLICA_SIZE];

public:
    ListaTablicowa() {}

    // Wypisuje listę na stdout, format [1, 2, 3, ..., n]
    void printList()
    {
        std::cout << "[";
        for (int i = 0; i < lastIndex; i++) {
            std::cout << tab[i];
            if (i + 1 < lastIndex) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }

    // Zwraca pozycję elementu pierwszego
    int First()
    {
        if (lastIndex == 0)
            return -1;
        return 0;
    };

    // Zwraca pozycję za ostatnim elementem
    int End()
    {
        return lastIndex;
    };

    /*
    Zwraca indeks następnego elementu po p
    Jeżeli nie istnieje taki element, zwraca -1
    */
    int Next(int p)
    {
        if (p < lastIndex)
            return p + 1;
        return -1;
    };

    /*
    Zwraca indeks poprzedniego elementu przed p
    Jeżeli nie istnieje taki element, zwraca -1
    */
    int Previous(int p)
    {
        if (p > 0)
            return p - 1;
        else
            return -1;
    };

    /*
     * Wstawia x do komórki o indeksie p.
     * Zwraca true jeżeli operacja się powiodła
     * i false w przeciwnym wypadku.
     */
    bool Insert(element x, int p)
    {
        if (p > lastIndex)
            p = lastIndex;
        if (p < 0 || p >= TABLICA_SIZE)
            return false;

        // przesuwamy elementy do przodu aby
        // zrobić miejsce i potem wstawiamy
        for (int i = lastIndex - 1; i >= p; --i)
            tab[i + 1] = tab[i];
        tab[p] = x;
        lastIndex++;
        return true;
    };

    /*
     * Usuwa element na indeksie p.
     * Zwraca true jeżeli operacja się powiodła
     * i false w przeciwnym wypadku.
     */
    bool Delete(int p)
    {
        if (p > lastIndex)
            p = lastIndex;
        else if (p < 0)
            return false;

        // przesuwamy wszyskie elementy do tyłu
        // tym samym zastępując element który usuwamy
        for (int i = p; i < lastIndex; ++i)
            tab[i] = tab[i + 1];
        lastIndex--;
        return true;
    }

    /*
     * Zwraca pozycję elementu x w liście.
     * Jeżeli nie istnieje, zwraca wartość -1.
     */
    int Locate(element x)
    {
        for (int i = 0; i < lastIndex; ++i)
            if (tab[i] == x)
                return i;
        return -1;
    }

    /*
     * Zwraca element znajdujący się w liście w komórce o indeksie p, jeśli
     * pozycja p jest poprawna - wpp zwraca pusty element.
     */
    element Retrieve(int p)
    {
        if (p < 0 || p >= lastIndex)
            return element();
        return tab[p];
    }

    // Zwraca wielkość tablicy
    int getCapacity(){
        return TABLICA_SIZE;
    }
};

// STOS - WSKAŹNIKI --------------------------------------------------------------------------------------------- //

/*
1. Proszę zaimplementować stos z wykorzystaniem wskaźnikowej implementacji listy. Należy umożliwić przechowywanie na stosie danych dowolnego typu.
Wymagane metody:
- void push(element x) - dodaje element na stos,
- element pop() - pobiera (i usuwa) element ze szczytu stosu,
- element top() - zwraca element znajdujący się na szczycie stosu (bez usuwania),
- void makenull() - usuwa wszystkie elementy ze stosu,
- boolean empty() - sprawdza, czy stos jest pusty.
*/

template <typename element>
class StosWskaznikowy : public ListaJednokierunkowa<element>
{
public:
    // dodaje element x na stos
    void push(element x)
    {
        cellJedn<element> *last = this->Last();
        this->Insert(x, last);
    }

    // pobiera i usuwa ostatni element ze stosu
    element pop()
    {
        cellJedn<element> *last = this->Last();
        if (last)
        {
            element value = last->data;
            this->Delete(last);
            return value;
        }
        else
            return element();
        // jeśli stos pusty, zwracamy pusty element
    }

    // zwraca element znajdujący się na początku stosu (bez usuwania)
    element top()
    {
        cellJedn<element> *last = this->Last();
        return last ? last->data : element();
    }

    // usuwa wszystkie elementy ze stosu
    void makenull()
    {
        while (this->First())
            this->Delete(this->First());
    }

    // sprawdza, czy stos jest pusty
    bool empty()
    {
        return this->Last() == nullptr;
    }
};

// STOS - TABLICA -------------------------------------------------------------------------------------------- //

/*
2. Proszę zaimplementować stos z wykorzystaniem tablicy. Należy umożliwić przechowywanie na stosie danych dowolnego typu.
Wymagane metody:
- boolean push(element x) - dodaje element na stos,
- element pop() - pobiera (i usuwa) element ze szczytu stosu,
- element top() - zwraca element znajdujący się na szczycie stosu (bez usuwania),
- void makenull() - usuwa wszystkie elementy ze stosu,
- boolean empty() - sprawdza, czy stos jest pusty.
*/

template <typename element>
class StosTablicowy : public ListaTablicowa<element>
{
public:
    // dodaje element x na stos
    bool push(element x)
    {
        if (this->lastIndex >= this->getCapacity())
            return false;
        this->Insert(x, this->End());
        return true;
    }

    // pobiera i usuwa ostatni element ze stosu
    element pop()
    {
        if (this->End())
        {
            element frontElement = this->Retrieve(this->End() - 1);
            this->Delete(this->End() - 1);

            return frontElement;
        }
        else
            return element();
        // jeśli stos pusty, zwracamy pusty element
    }

    // zwraca element znajdujący się na początku stosu (bez usuwania)
    element top()
    {
        return this->Retrieve(this->End() - 1);
    }

    // usuwa wszystkie elementy ze stosu
    void makenull()
    {
        while (this->Delete(this->End() - 1));
    }

    // sprawdza, czy stos jest pusty
    bool empty()
    {
        return this->End() == 0;
    }
};

// MAIN -------------------------------------------------------------------------------------------- //

int main(int argc, char const *argv[])
{
    // STOS - WSKAŹNIKOWY
    PRINTSP("STOS - WSKAŹNIKI");
    StosWskaznikowy<int> stosWsk;

    PRINTSP("Pusty stos: ");
    stosWsk.print();

    stosWsk.push(1);
    stosWsk.push(2);
    stosWsk.push(3);

    PRINTSP("Stos z 3 elementami: ");
    stosWsk.print();

    std::cout << "Pierwszy element: " << stosWsk.top() << std::endl;
    while (!stosWsk.empty())
        std::cout << "Wyjęty element: " << stosWsk.pop() << std::endl;

    stosWsk.makenull(); // czysta formalność aby sprawdzić, czy działa metoda.
                        // stos i tak już jest pusty po pętli.

    PRINTSP("Pusty stos: ");
    stosWsk.print();

    // STOS TABLICOWY
    PRINTSP("STOS - TABLICA");
    StosTablicowy<int> stosTab;

    PRINTSP("Pusty stos: ");
    stosTab.printList();

    stosTab.push(1);
    stosTab.push(2);
    stosTab.push(3);

    PRINTSP("Stos z 3 elementami: ");
    stosTab.printList();

    std::cout << "Pierwszy element: " << stosTab.top() << std::endl;
    while (!stosTab.empty())
        std::cout << "Wyjęty element: " << stosTab.pop() << std::endl;

    stosTab.makenull(); // czysta formalność aby sprawdzić, czy działa metoda.
                        // stos i tak już jest pusty po pętli.

    PRINTSP("Pusty stos: ");
    stosTab.printList();

    return 0;
}
