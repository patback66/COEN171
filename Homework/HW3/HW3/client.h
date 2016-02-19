#ifndef CLIENT_H
#define CLIENT_H
#include "person.h"

class Client : public Person
{
public:
    Client();
    Client(string n, string a, int c);
    void purchaseBook();
};

#endif // CLIENT_H
