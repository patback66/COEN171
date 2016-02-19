#include "client.h"

//Default constructor
Client::Client() {
    name = "John Smith";
    address = "1234 Sunshine Stree";
    creditCard = 1234567890;
}

//Constructor
Client::Client(string n, string a, int c){
    name = n;
    address = a;
    creditCard = c;
}
