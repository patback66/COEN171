#include "person.h"

//default constructor
Person::Person() {
    name = "John Smith";
    address = "1234 Sunshine Street";
    creditCard = 2398479872;
}
//parameterized constructor
Person::Person(string n, string a, int cc) {
    name = n;
    address = a;
    creditCard = cc;
}

string Person::getAddress(){
    return address;
}

void Person::setAddress(string a){
    address = a;
}

string Person::getName(){
    return name;
}

void Person::setName(string n) {
    name = n;
}

int Person::getCreditCard() {
    return creditCard;
}

void Person::setCreditCard(int cc) {
    creditCard = cc;
}
