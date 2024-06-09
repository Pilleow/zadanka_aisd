#include <iostream>
#include <functional>
/*
 * klasa Hashmap została napisana tak, aby możliwe było użycie dowolnych obiektów
 * jako klucz i wartość, zwłaszcza liczb naturalnych. Dodatkowo, należy podać
 * zmienną maxSize, która określa stałą wielkość Hashmapy.
 */
template <typename KeyT, typename ValueT, std::size_t maxSize>
class Hashmap {
private:
    // tablica "dwuwymiarowa", gdzie trzymamy parę (klucz, wartość)
    std::array<std::pair<KeyT, ValueT>, maxSize> table;

    size_t hashFunction(const KeyT& key) const {
        // bierzemy hash klucza i ograniczamy go do zakresu [0, maxSize - 1]
        return std::hash<KeyT>{}(key) % maxSize;
    }

public:
    /*
     * Podstawowy konstruktor. Wypełnia hashmapę pustymi obiektami.
     */
    Hashmap() {
        // tworzymy tablicę z wyzerowanymi (pustymi) danymi
        for (auto& entry : table) {
            entry = std::make_pair(KeyT{}, ValueT{});
        }
    }

    /*
     * Metoda dodaje parę (key, value) do hashmapy. Na początku, metoda oblicza funkcję
     * haszującą klucza.
     *
     * Następnie w, pętli, przechodzi przez całą hashmapę cyklicznie (tzn. jak dojdziemy
     * do końca mapy to zapętlamy do początku jeśli nie sprawdziliśmy wszystkich elementów),
     * rozpoczynając przechodzenie od miejsca, do którego wskazuje wartość hash klucza.
     *
     * Jeśli to miejsce jest zajęte, dodajemy do klucza i ewentualnie zapętlamy (jak wyżej).
     * Jeśli miejsce jest puste, wstawiamy PARĘ (key, value) pod ten indeks.
     *
     * Cała metoda ma złożoność czasową O(n) i pamięciową O(1).
     */
    void addElement(const KeyT& key, const ValueT& value) {
        // przechodzimy przez tablicę zaczynając na indeksie = hash(key)
        size_t index = hashFunction(key);

        for (size_t i = 0; i < maxSize; ++i) {
            if (table[index].first == KeyT{}) {
                table[index] = std::make_pair(key, value);
                return;
            } else if (table[index].first == key) throw std::invalid_argument("\nElement o podanym kluczu znajduje się już w hashmapie.");
            // jeśli nie patrzymy na parę z naszym kluczem, idziemy na następne pole
            index = (index + 1) % maxSize;
        }

        // przeszliśmy przez wszystkie pola w pamięci, brak miejsca na nowy element
        throw std::out_of_range("Brak miejsca na nowy element - wszystkie klucze są zajęte.");
    }

    /*
     * Metoda wyszukuje wartosć value w hashmapie. Na początku, metoda oblicza funkcję
     * hashującą klucza.
     *
     * Następnie, w pętli, przechodzi przez całą hashmapę cyklicznie, rozpoczynając
     * przechodzenie od miejsca, do którego wskazuje wartość hash klucza.
     *
     * W każdym miejscu w hashmapie zapisane są PARY (savedKey, savedValue). Jeżeli zgadzają
     * się wartość ORAZ klucz, to zwracamy wartość. Jeśli nie, idziemy dalej.
     *
     * Cała metoda ma złożoność czasową O(n) i pamięciową O(1).
     */
    ValueT findElement(const KeyT& key) const {
        // przechodzimy przez tablicę zaczynając na indeksie = hash(key)
        size_t index = hashFunction(key);

        for (size_t i = 0; i < maxSize; ++i) {
            const auto& entry = table[index];
            const auto& storedKey = entry.first;
            const auto& storedValue = entry.second;
            if (storedKey == key) {
                return storedValue;
            }
            // jeśli nie patrzymy na parę z naszym kluczem, idziemy na następne pole
            index = (index + 1) % maxSize;
        }

        // przeszliśmy przez wszystkie pola w pamięci, nie znaleźliśmy elementu
        throw std::invalid_argument("Element o podanym kluczu nie istnieje.");
    }

    /*
     * Metoda usuwa wartość pod kluczem key w hashmapie. Na początku, metoda oblicza funkcję
     * hashującą klucza.
     *
     * Następnie, w pętli, przechodzi przez całą hashmapę cyklicznie, rozpoczynając
     * przechodzenie od miejsca, do którego wskazuje wartość hash klucza.
     *
     * Jeśli klucz zgadza się z kluczem zapisanym na danym miejscu, czyścimy dane na tej pozycji.
     *
     * Cała metoda ma złożoność czasową O(n) i pamięciową O(1).
     */
    void removeElement(const KeyT& key) {
        size_t index = hashFunction(key);
        // przechodzimy przez tablicę zaczynając na indeksie = hash(key)

        for (size_t i = 0; i < maxSize; ++i) {
            const auto& entry = table[index];
            const auto& storedKey = entry.first;
            if (storedKey == key) {
                table[index] = std::make_pair(KeyT{}, ValueT{});
                return;
            }
            // jeśli nie patrzymy na parę z naszym kluczem, idziemy na następne pole
            index = (index + 1) % maxSize;
        }

        // przeszliśmy przez wszystkie pola w pamięci, nie znaleźliśmy elementu
        throw std::invalid_argument("Element o podanym kluczu nie istnieje.");
    }
};

int main() {
    Hashmap<std::string, int, 9> hm_of_squares;
    int i;

    std::cout << "\n==== DODAWANIE ====" << std::endl;
    std::cout << "Dostaniemy błąd o braku miejsca na nowy element.\nTo jest efekt zamierzony, ponieważ w teście dodajemy więcej elementów, niż jest miejsca w hashmapie.\n" << std::endl;
    try {
        for (i = 2; i < 15; i++) {
            hm_of_squares.addElement(std::to_string(i), i * i);
            std::cout << "      ADD key=\"" << i << "\"" << " value=" << i << " -> success" << std::endl;
        }
    } catch (const std::out_of_range& e) {
        std::cerr << "\nBłąd zamierzony: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "\n\nTO NIE POWINNO SIĘ STAĆ: " << e.what() << std::endl;
    }

    std::cout << "\nTeraz spróbujemy dodać ponownie klucz \"5\", \nktóry już znajduje się w hashmapie. Dostaniemy błąd o istnieniu takiego klucza.\n" << std::endl;
    try {
        hm_of_squares.addElement("5", 0);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Błąd zamierzony: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "\n\nTO NIE POWINNO SIĘ STAĆ: " << e.what() << std::endl;
    }

    std::cout << "\n==== WYSZUKIWANIE ====" << std::endl;
    std::cout << "Dostaniemy błąd o nieistniejącym elemencie podczas wyszukiwania.\nTo jest efekt zamierzony, ponieważ w teście wyszukujemy klucze, które nie zostały dodane.\n" << std::endl;
    try {
        for (i = 2; i < 15; i++) {
            int r = hm_of_squares.findElement(std::to_string(i));
            std::cout << "      GET key=" << i << " -> " << r << std::endl;
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "\nBłąd zamierzony: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "\n\nTO NIE POWINNO SIĘ STAĆ: " << e.what() << std::endl;
    }

    std::cout << "\n==== USUWANIE ====" << std::endl;
    std::cout << "Dostaniemy błąd o nieistniejącym elemencie podczas usuwania - to jest efekt zamierzony.\n" << std::endl;
    try {
        for (i = 2; i < 15; i++) {
            hm_of_squares.removeElement(std::to_string(i));
            std::cout << "      DELETE key=" << i << " -> success" << std::endl;
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "\nBłąd zamierzony: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "\n\nTO NIE POWINNO SIĘ STAĆ: " << e.what() << std::endl;
    }

    std::cout << "\n==== WYSZUKIWANIE ====" << std::endl;
    std::cout << "Dostaniemy błąd o nieistniejącym elemencie podczas wyszukiwania, bo wszystko usunęliśmy.\nTo jest efekt zamierzony.\n" << std::endl;
    try {
        for (i = 2; i < 15; i++) {
            int r = hm_of_squares.findElement(std::to_string(i));
            std::cout << "      GET key=" << i << " -> " << r << std::endl;
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "\nBłąd zamierzony: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "\n\nTO NIE POWINNO SIĘ STAĆ: " << e.what() << std::endl;
    }

    std::cout << "\n==== KONIEC :) ====" << std::endl;

    return 0;
}
