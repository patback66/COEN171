#include "store.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <strings.h>
#include <algorithm>

using namespace std;

Store::Store()
{
    readToInventory();
}
//Read from csv file
bool Store::readToInventory() {
    ifstream file("inventory.csv");
    if(file.is_open()) {
        while(file.good()) {
            /*
             * Csv line should read as "Title","Author",isbn,quantity,price
             */
            string name, author, isbn, quantity, price;
            getline(file, name, ',');
            getline(file, author, ',');
            getline(file, isbn, ',');
            getline(file, quantity, ',');
            getline(file, price, ',');
            //strip the newline from the file if read in
            name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());
            //cout << name << " " << author << " " << isbn << " " << quantity << " " << price << endl;
            inventory.push_back(new book(name, author, stoi(isbn), stoi(quantity), stof(price)));
        }
        file.close();
        return true;
    } else {
        file.close();
        return false;
    }

}

//Persist to the csv file
bool Store::writeToInventory(){
    ofstream file("inventory.csv");
    if(file.is_open()) {
        for(int i = 0; i < inventory.size(); i++){
            string ln = inventory[i]->getName() + ','
                    + inventory[i]->getAuthor() + ','
                    + to_string(inventory[i]->getIsbn()) + ','
                    + to_string(inventory[i]->getStock()) + ','
                    + to_string(inventory[i]->getPrice());
            if(i+1 < inventory.size()) //not the last line to write
                ln+=",\n"; //don't add more commas on the last line
            file << ln;
         }
         file.close();
        return true;
    } else {
        file.close();
        return false;
    }
}

//clean allocated space
Store::~Store(){
    writeToInventory();
    for(int i = 0; i < inventory.size(); i++){
        delete(inventory[i]);
    }
}

void Store::displayBanner() {
    cout << "/////////////////////////////////////////////\n";
    cout << "//////////Welcome to the bookstore!//////////\n";
    cout << "/////////////////////////////////////////////\n";
}

//display formatted inventory
void Store::printInventory(bool showBanner){
    if(showBanner)
        displayBanner();
    for(int i = 0; i < inventory.size(); i++){
        cout << "(" << to_string(i+1) << ") Title: " << inventory[i]->getName() << endl;
        cout << "\t Author:" << inventory[i]->getAuthor();
        cout << "\t ISBN: " << to_string(inventory[i]->getIsbn()) << endl;
        cout << "\t Quantity: " << to_string(inventory[i]->getStock());
        cout << "\t Price: $" << to_string(inventory[i]->getPrice()) << endl;
    }
}

//add a book to the inventory
void Store::addBook(string title, string author, int isbn, int quantity, float price){
    inventory.push_back(new book(title, author, isbn, quantity, price));
    //save
    writeToInventory();
}
