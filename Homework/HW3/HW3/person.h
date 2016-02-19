#ifndef PERSON_H
#define PERSON_H
#include <string>
using namespace std;

class Person
{
protected:
    string name;
    string address;
    int creditCard;
public:
    Person();
    Person(string, string, int);
    string getName();
    void setName(string);
    void setAddress(string);
    string getAddress();
    void setCreditCard(int);
    int getCreditCard();
};

#endif // PERSON_H
