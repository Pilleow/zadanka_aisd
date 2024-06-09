/*
Zadanie 2 - lista wskaźnikowa
Autor: Igor Zamojski

Proszę utworzyć implementację listy wiązanej jednokierunkowej
i dwukierunkowej z wykorzystaniem szablonów (lista powinna
przechowywać elementy dowolnego typu)
*/
#include <iostream>
#include <cassert>
#define PRINTSP(s) (std::cout << std::endl << s << std::endl)

// LISTA DWUKIERUNKOWA --------------------------------------------------------------------------------------- //

template <typename element>
struct cellDwu {
    element data;
    cellDwu* next;
    cellDwu* prev;

    cellDwu(element value) : data(value), next(nullptr), prev(nullptr) {}
};

template <typename element>
class ListaDwukierunkowa
{
    protected:
        /* głowa listy */
        cellDwu<element>* header;
    public:
        /*
        konstruktor
        tworzymy głowę listy
        */
        ListaDwukierunkowa() : header(nullptr) {}
         /*
         destruktor
         usuwamy wszystkie elementy (zwalniamy miejsce)
         */
        ~ListaDwukierunkowa() {
            while (header) {
                cellDwu<element>* temp = header;
                header = header->next;
                delete temp;
            }
        }

        /*
        wstawia element x na pozycję next komórki o wskaźniku p
        (lub w przypadku pustej listy tworzy komórkę z elementem x w miejscu głowy listy)
        */
        void Insert(element x, cellDwu<element>* p) {
            cellDwu<element>* newCell = new cellDwu<element>(x);

            if (p == nullptr) { // wstawiamy na początek listy
                newCell->next = header;
                if (header) header->prev = newCell;
                header = newCell;
            } else { // wstawiamy za wskazaną komórkę
                newCell->next = p->next;
                newCell->prev = p;
                if (p->next) p->next->prev = newCell;
                p->next = newCell;
            }
        }

        /*
        usuwa komórkę z pozycji next komórki o wskaźniku p i zwraca true
        zwraca false, gdy usunięcie nie jest możliwe
        */
        bool Delete(cellDwu<element>* p) {
            if (p == nullptr || header == nullptr) return false;

            if (p->prev) p->prev->next = p->next;
            else header = p->next; // usuwamy z początku listy
            if (p->next) p->next->prev = p->prev;

            delete p;
            return true;
        }

        /*
        zwraca element komórki o wskaźniku p
        zwraca pustą wartość dla p = nullptr
        */
        element Retrieve(cellDwu<element>* p) {
            return p != nullptr ? p->data : element();
          }

        /*
        zwraca wskaźnik do pierwszej komórki z elementem x
        */
        cellDwu<element>* Locate(element x) {
            cellDwu<element>* current = header;
            while (current != nullptr && current->data != x) current = current->next;
            return current;
        }

        /*
        zwraca wskaźnik do pierwszej komórki na liście
        */
        cellDwu<element>* First() {
            return header;
        }

        /*
        zwraca wskaźnik do kolejnej komórki po komórce o wskaźniku p
        zwraca nullptr dla p = nullptr
        */
        cellDwu<element>* Next(cellDwu<element>* p) {
            return p != nullptr ? p->next : nullptr;
        }

        /*
        zwraca wskaźnik do komórki poprzedzającej komórkę o wskaźniku p
        zwraca nullptr dla p = nullptr
        */
        cellDwu<element>* Previous(cellDwu<element>* p) {
            return p != nullptr ? p->prev : nullptr;
        }

        /*
        zwraca wskaźnik do ostatniej komórki na liście
        */
        cellDwu<element>* Last() {
            cellDwu<element>* current = header;
            while (current != nullptr && current->next != nullptr) current = current->next;
            return current;
        }

        /*
        wyświetla wszystkie elementy listy
        */
        void print() {
            cellDwu<element>* current = header;
            std::cout << "[";
            while (current != nullptr) {
                std::cout << current->data;
                if (current->next != nullptr) std::cout << ", ";
                current = current->next;
            }
            std::cout << "]" << std::endl;
        }
};

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


int main() {

    PRINTSP("LISTA JEDNOKIERUNKOWA");
    // TESTOWANIE LISTY JEDNOKIERUNKOWEJ -------------------------------------------------- //

    ListaJednokierunkowa<int> lista;
    cellJedn<int>* cellToDelete;
    cellJedn<int>* prevCellToDelete;

    PRINTSP("Pusta lista (zaraz po utworzeniu): ");
    lista.print();
    // działa Insert?

    lista.Insert(1, nullptr);
    lista.Insert(2, nullptr);
    lista.Insert(3, nullptr);

    PRINTSP("Lista z trzema elementami: ");
    lista.print();
    // działa First?

    cellJedn<int>* firstCell = lista.First();
    lista.Insert(4, firstCell);
    lista.Insert(5, firstCell->next);

    PRINTSP("Lista z pięcioma elementami:");
    lista.print();
    // działa Locate i Delete?

    cellToDelete = lista.Locate(3);
    prevCellToDelete = lista.Previous(cellToDelete);

    assert(cellToDelete != nullptr);
    assert(lista.Locate(99) == nullptr);
    assert(lista.Delete(cellToDelete) == true);
    assert(lista.Delete(prevCellToDelete) == false);

    PRINTSP("Lista z usuniętym elementem '3':");
    lista.print();
    // działa Last?

    cellToDelete = lista.Last();
    prevCellToDelete = lista.Previous(cellToDelete);
    assert(lista.Delete(cellToDelete) == true);
    assert(lista.Delete(prevCellToDelete) == true);

    PRINTSP("Lista z usuniętym elementem '1' i '2':");
    lista.print();
    // działa Retrieve?

    PRINTSP("Wartość ostatniej komórki:");
    std::cout << lista.Retrieve(lista.Last()) << std::endl;
    std::cout << std::endl;

    PRINTSP("LISTA DWUKIERUNKOWA");
    // TESTOWANIE LISTY DWUKIERUNKOWEJ ---------------------------------------------------- //

    ListaDwukierunkowa<int> lista2;
    cellDwu<int>* cellToDelete2;
    cellDwu<int>* prevCellToDelete2;

    PRINTSP("Pusta lista (zaraz po utworzeniu): ");
    lista2.print();
    // działa Insert?

    lista2.Insert(1, nullptr);
    lista2.Insert(2, nullptr);
    lista2.Insert(3, nullptr);

    PRINTSP("Lista z trzema elementami: ");
    lista2.print();
    // działa First?

    cellDwu<int>* firstCell2 = lista2.First();
    lista2.Insert(4, firstCell2);
    lista2.Insert(5, firstCell2->next);

    PRINTSP("Lista z pięcioma elementami:");
    lista2.print();
    // działa Locate i Delete?

    cellToDelete2 = lista2.Locate(3);
    prevCellToDelete2 = lista2.Previous(cellToDelete2);

    assert(cellToDelete2 != nullptr);
    assert(lista2.Locate(99) == nullptr);
    assert(lista2.Delete(cellToDelete2) == true);
    assert(lista2.Delete(prevCellToDelete2) == false);

    PRINTSP("Lista z usuniętym elementem '3':");
    lista.print();
    // działa Last?

    cellToDelete2 = lista2.Last();
    prevCellToDelete2 = lista2.Previous(cellToDelete2);
    assert(lista2.Delete(cellToDelete2) == true);
    assert(lista2.Delete(prevCellToDelete2) == true);

    PRINTSP("Lista z usuniętym elementem '1' i '2':");
    lista2.print();
    // działa Retrieve?

    PRINTSP("Wartość ostatniej komórki:");
    std::cout << lista2.Retrieve(lista2.Last()) << std::endl;
    std::cout << std::endl;

    return 0;
}
