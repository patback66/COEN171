#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class book
{
protected:
    string name;
    string author;
    int isbn;
    int stock;
    float price;
public:
    book() {name="", author="", isbn=0; stock=0; price=0.0;}
    book(string n="", string a="", int i=0, int q=0, float p=0.0)
        : name(n), author(a), isbn(i), stock(q), price(p){}
    void setName(string n);
    string getName();
    void setAuthor(string a);
    string getAuthor();
    void setIsbn(int i);
    int getIsbn();
    void setStock(int q);
    int getStock();
    void setPrice(float p);
    float getPrice();
    bool addOneBook();
    bool subOneBook();
};

#endif // BOOK_H
