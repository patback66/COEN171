#include "book.h"
#include <stdlib.h>
// name, author,isbn, price and stock
void book::setName(string n) {
    name = n;
}

string book::getName() {
    return name;
}

void book::setAuthor(string a) {
    author = a;
}

string book::getAuthor() {
    return author;
}

void book::setIsbn(int i) {
    isbn = i;
}

int book::getIsbn() {
    return isbn;
}

void book::setStock(int q) {
    stock = q;
}

int book::getStock() {
    return stock;
}

void book::setPrice(float p) {
    price = p;
}

float book::getPrice(){
    return price;
}

bool book::addOneBook() {
    stock++;
    return true;
}

bool book::subOneBook() {
    if(stock>0) {
        stock--;
        return true;
    } else {
        return false;
    }
}
