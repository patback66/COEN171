#ifndef OWNER_H
#define OWNER_H
#include "person.h"
#include "store.h"
#include "book.h"
#include "vector"
#include "client.h"

class Owner : public Person
{
private:
    Store store;
    vector<Client*> clients;
public:
    Owner();
    Owner(string);
    ~Owner();
    void displayInventory();
    void sellBook(book b, Person p);
    bool updateBook(int index);
    void displayBanner();
    void displayInventory(bool showBanner);
    bool save();
    bool updateABook();
    bool modifyBooks();
    bool addABook();
    void sellBook(int isNew);
    void printClients();
    bool readToClients();
    bool writeToClients();
};

#endif // OWNER_H
