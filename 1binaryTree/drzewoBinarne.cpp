#include <iostream>
#include <stack>
#include <bits/stdc++.h>

#define PRINT(x) (cout << x << endl) 

using namespace std;

template <typename T>
struct cell
{
    T data;
    cell<T>* left;
    cell<T>* right;

    explicit cell(T value) : data(value), left(nullptr), right(nullptr) {}
};


template <typename T>
class BinaryTreeWskaznikowy {
    private:
        cell<T>* root;

    public:
    BinaryTreeWskaznikowy() : root(nullptr) {}

    // wyszukiwanie wgłąb, zwraca wskaznik do węzła o wartości `dataToFind`.
    // jeżeli taki węzeł nie istnieje, zwraca `nullptr`.
    //
    // `orderType = 0` - preorder: przetwarzamy węzeł a nastepnie potomkow
    //
    // `orderType = 1` - inorder: odwiedzamy węzeł, przetwarzamy lewego potomka, potem dany węzeł, potem prawego potomka
    //
    // `orderType = 2` - postorder: odwiedzamy węzeł, najpierw przetwarzamy potomków, potem przetwarzamy węzeł
    cell<T>* DFS(T dataToFind, int orderType) {
        if (root == nullptr) return nullptr;

        stack<cell<T>*> s;
        unordered_set<cell<T>*> visited;

        s.push(root);
        while (!s.empty()) {

            cell<T>* v = s.top();
            s.pop();
            if (visited.find(v) == visited.end()) {
                visited.insert(v);
                switch (orderType) {
                    case 0:  // preorder
                        if (v->data == dataToFind) return v;
                        if (v->left != nullptr) s.push(v->left);
                        if (v->right != nullptr) s.push(v->right);
                        break;
                    case 1:  // inorder
                        if (v->left != nullptr) s.push(v->left);
                        if (v->data == dataToFind) return v;
                        if (v->right != nullptr) s.push(v->right);
                        break;
                    default:  // postorder
                        if (v->left != nullptr) s.push(v->left);
                        if (v->right != nullptr) s.push(v->right);
                        if (v->data == dataToFind) return v;
                        break;
                }
            }

        }
        return nullptr;
    }

    // dodawanie elementu na początek drzewa.
    // jeżeli na miejscu wstawienia istnieje już jakiś obiekt,
    // ten obiekt jest zastępowany.
    //
    // zwraca `0` jeżeli operacja się powiodła, 
    //        `1` jeżeli został dodany korzeń. 
    //        `2' jeżeli komórka rodzica nie została odnaleziona.
    int insert(T dataToInsert, bool insertToTheLeft) {
        return insert(dataToInsert, T(), insertToTheLeft);
    }

    // dodawanie elementu pod komórkę z wartością `parentData`.
    // jeżeli na miejscu wstawienia istnieje już jakiś obiekt,
    // ten obiekt jest zastępowany.
    //
    // zwraca `0` jeżeli operacja się powiodła, 
    //        `1` jeżeli został dodany korzeń. 
    //        `2' jeżeli komórka rodzica nie została odnaleziona.
    int insert(T dataToInsert, T parentData, bool insertToTheLeft) {
        auto* newCell = new cell<T>(dataToInsert);
        if (this->root == nullptr) {
            this->root = newCell;
            return 1;
        } 
        cell<T>* parentCell = DFS(parentData, 0);
        if (parentCell == nullptr) return 2;
        if (insertToTheLeft) parentCell->left = newCell;
        else parentCell->right = newCell;
        return 0;
    }
};


int main()
{
    BinaryTreeWskaznikowy<int> btw;
    PRINT("\nNic nie powinno byc:");
    PRINT(btw.DFS(8, 0));
    PRINT(btw.DFS(8, 1));
    PRINT(btw.DFS(8, 2));

    PRINT("\nDodajemy...");
    btw.insert(1, true);
    btw.insert(2, 1, true);
    btw.insert(3, 1, false);
    btw.insert(4, 2, true);
    btw.insert(7, 4, false);
    btw.insert(5, 3, true);
    btw.insert(6, 3, false);
    btw.insert(99, 5, false);
    btw.insert(8, 5, false); // zastępuje poprzedni

    PRINT("\nKoniec! Teraz mamy cos:");
    PRINT(btw.DFS(8, 0));
    PRINT(btw.DFS(8, 1));
    PRINT(btw.DFS(8, 2));

    PRINT("\nA teraz znowu nic:");
    PRINT(btw.DFS(99, 0));
    PRINT(btw.DFS(99, 1));
    PRINT(btw.DFS(99, 2));

    PRINT("\nUdalo sie!");
    return 0;
}
