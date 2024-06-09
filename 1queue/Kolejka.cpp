/*
Zadanie 3 - kolejka
Autor: Igor Zamojski
*/
#include <iostream>
#define PRINTSP(s) (std::cout << std::endl << s << std::endl)

/*
1. Proszę zaimplementować kolejkę z wykorzystaniem wskaźnikowej implementacji listy. Należy umożliwić przechowywanie w kolejce danych dowolnego typu.
Wymagane metody:
- void put(element x) - dodaje element do kolejki,
- element get() - pobiera (i usuwa) pierwszy element z kolejki,
- element front() - zwraca element znajdujący się na początku kolejki (bez usuwania),
- void makenull() - usuwa wszystkie elementy z kolejki,
- boolean empty() - sprawdza, czy kolejka jest pusta.
*/

// LISTA JEDNOKIERUNKOWA ------------------------------------------------------------------------------------- //

template <typename element>
struct cellJedn {
    element data;
    cellJedn* next;

    cellJedn(element value) : data(value), next(nullptr) {}
};

template <typename element>
class ListaJednokierunkowa
{
    protected:
        /* głowa listy */
        cellJedn<element>* header;
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
        ~ListaJednokierunkowa() {
            while (header) {
                cellJedn<element>* temp = header;
                header = header->next;
                delete temp;
            }
        }

        /*
        wstawia element x na pozycję next komórki o wskaźniku p
        (lub w przypadku pustej listy tworzy komórkę z elementem x w miejscu głowy listy)
        */
        void Insert(element x, cellJedn<element>* p) {
            cellJedn<element>* newCell = new cellJedn<element>(x);

            if (p == nullptr) { // wstawiamy na początek listy
                newCell->next = header;
                header = newCell;
            } else { // wstawiamy za wskazaną komórkę
                newCell->next = p->next;
                p->next = newCell;
            }
        }

        /*
        usuwa komórkę z pozycji next komórki o wskaźniku p i zwraca true
        zwraca false, gdy usunięcie nie jest możliwe
        */
        bool Delete(cellJedn<element>* p) {
            if (p == nullptr || header == nullptr) return false;
            cellJedn<element>* prev = Previous(p);
            if (prev) prev->next = p->next;
            else header = p->next;
            delete p;
            return true;
        }

        /*
        zwraca element komórki o wskaźniku p
        zwraca pustą wartość dla p = nullptr
        */
        element Retrieve(cellJedn<element>* p) {
            return p != nullptr ? p->data : element();
          }

        /*
        zwraca wskaźnik do pierwszej komórki z elementem x
        */
        cellJedn<element>* Locate(element x) {
            cellJedn<element>* current = header;
            while (current != nullptr && current->data != x) current = current->next;
            return current;
        }

        /*
        zwraca wskaźnik do pierwszej komórki na liście
        */
        cellJedn<element>* First() {
            return header;
        }

        /*
        zwraca wskaźnik do kolejnej komórki po komórce o wskaźniku p
        zwraca nullptr dla p = nullptr
        */
        cellJedn<element>* Next(cellJedn<element>* p) {
            return p != nullptr ? p->next : nullptr;
        }

        /*
        zwraca wskaźnik do komórki poprzedzającej komórkę o wskaźniku p
        zwraca nullptr dla p = nullptr
        */
        cellJedn<element>* Previous(cellJedn<element>* p) {
            cellJedn<element>* current = header;
            while (current != nullptr && current->next != p) current = current->next;
            return current;
        }

        /*
        zwraca wskaźnik do ostatniej komórki na liście
        */
        cellJedn<element>* Last() {
            cellJedn<element>* current = header;
            while (current != nullptr && current->next != nullptr) current = current->next;
            return current;
        }

        /*
        wyświetla wszystkie elementy listy
        */
        void print() {
            cellJedn<element>* current = header;
            std::cout << "[";
            while (current != nullptr) {
                std::cout << current->data;
                if (current->next != nullptr) std::cout << ", ";
                current = current->next;
            }
            std::cout << "]" << std::endl;
        }
};

// KOLEJKA ------------------------------------------------------------------------------------- //

template <typename element>
class Kolejka : public ListaJednokierunkowa<element> {
public:
    // dodaje element x do kolejki
    void put(element x) {
        cellJedn<element>* last = this->Last();
        this->Insert(x, last);
    }

    // pobiera i usuwa pierwszy element z kolejki
    element get() {
        cellJedn<element>* first = this->First();
        if (first) {
            element value = first->data;
            this->Delete(first);
            return value;
        } else return element(); 
        // jeśli kolejka pusta, zwracamy pusty element
    }

    // zwraca element znajdujący się na początku kolejki (bez usuwania)
    element front() {
        cellJedn<element>* first = this->First();
        return first ? first->data : element();
    }

    // usuwa wszystkie elementy z kolejki
    void makenull() {
        while (this->First()) this->Delete(this->First());
    }

    // sprawdza, czy kolejka jest pusta
    bool empty() {
        return this->First() == nullptr;
    }
};

/*
2. Proszę zaimplementować kolejkę cykliczną z wykorzystaniem tablicy. Należy umożliwić przechowywanie w kolejce danych dowolnego typu.
Wymagane metody:
- boolean put(element x) - dodaje element do kolejki, jeśli jest miejsce,
- element get() - pobiera (i usuwa) pierwszy element z kolejki,
- element front() - zwraca element znajdujący się na początku kolejki (bez usuwania),
- void makenull() - usuwa wszystkie elementy z kolejki,
- boolean empty() - sprawdza, czy kolejka jest pusta.
*/

// KOLEJKA CYKLICZNA ------------------------------------------------------------------------------------- //

template <typename element>
class KolejkaCykliczna : public ListaJednokierunkowa<element> {
private:
    int capacity;    // wielkość kolejki cyklicznej
    int frontIndex;       // indeks pierwszego elementu
    int rear;        // indeks ostatniego elementu
    int size;        // aktualna ilość elementów w kolejce cyklicznej

public:
    // konstruktor
    KolejkaCykliczna(int capacity) : capacity(capacity), frontIndex(-1), rear(-1), size(0) {}

    // dodaje element x do kolejki jeżeli jest miejsce
    bool put(element x) {
        if ((rear + 1) % capacity == frontIndex) return false;  // kolejka jest pełna

        if (empty()) frontIndex = rear = 0;
        else rear = (rear + 1) % capacity;

        this->Insert(x, this->Last());
        size++;
        return true;
    }

    // pobiera i usuwa pierwszy element z kolejki cyklicznej
    element get() {
        if (empty()) return element(); // pusto

        element frontElement = this->Retrieve(this->First());
        this->Delete(this->First());

        if (frontIndex == rear) frontIndex = rear = -1;
        else frontIndex = (frontIndex + 1) % capacity;

        size--;
        return frontElement;
    }

    // zwraca element znajdujący się na początku kolejki cyklicznej (bez usuwania)
    element front() {
        if (empty()) return element();
        return this->Retrieve(this->First());
    }

    // usuwa wszystkie elementy z kolejki cyklicznej
    void makenull() {
        frontIndex = rear = -1;
        size = 0;
        while (this->First()) this->Delete(this->First());
    }

    // sprawdza, czy kolejka cykliczna jest pusta
    bool empty() {
        return size == 0;
    }
};

// MAIN ------------------------------------------------------------------------------------- //

int main() {

    PRINTSP("KOLEJKA");
    // KOLEJKA

    Kolejka<int> kolejka;
    PRINTSP("Pusta kolejka: ");
    kolejka.print();

    kolejka.put(1);
    kolejka.put(2);
    kolejka.put(3);
    PRINTSP("Kolejka z 3 elementami: ");
    kolejka.print();

    PRINTSP("Pierwszy element: ");
    std::cout << kolejka.front() << std::endl << std::endl;

    while (!kolejka.empty()) std::cout << "Wyjęty element: " << kolejka.get() << std::endl;

    PRINTSP("Pusta kolejka: ");
    kolejka.print();

    PRINTSP("KOLEJKA CYKLICZNA");
    // KOLEJKA CYKLICZNA

    KolejkaCykliczna<int> kolejkaCykliczna(5);
    PRINTSP("Pusta kolejka cykliczna: ");
    kolejkaCykliczna.print();

    kolejkaCykliczna.put(1);
    kolejkaCykliczna.put(2);
    kolejkaCykliczna.put(3);
    PRINTSP("Kolejka cykliczna z 3 elementami: ");
    kolejkaCykliczna.print();

    PRINTSP("Pierwszy element: ");
    std::cout << kolejkaCykliczna.front() << std::endl;

    while (!kolejkaCykliczna.empty()) std::cout << "Wyjęty element: " << kolejkaCykliczna.get() << std::endl;

    kolejkaCykliczna.makenull();
    PRINTSP("Pusta kolejka cykliczna: ");
    kolejkaCykliczna.print();

    return 0;
}
