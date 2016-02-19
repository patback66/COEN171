#ifndef STORE_H
#define STORE_H
#include "vector"
#include "book.h"
class Store
{
private:
public:
    vector<book*> inventory;
    Store();
    ~Store();
    bool readToInventory();
    bool writeToInventory();
    bool updateInventory();
    bool updateBook(book b);
    void addBook(string title, string author, int isbn, int quantity, float price);
    void printInventory(bool showBanner);
    void displayBanner();
};

#endif // STORE_H
