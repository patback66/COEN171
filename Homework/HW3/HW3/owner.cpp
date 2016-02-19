#include "owner.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "client.h"

using namespace std;

//Default constructor
Owner::Owner()
{
    store.readToInventory();
    readToClients();
}

//Constructor with owner name
Owner::Owner(string n){
    name = n;
    store.readToInventory();
    readToClients();
}

//Call to store to display owner, with option to show the banner
void Owner::displayInventory(bool showBanner){
    store.printInventory(showBanner);
}

//Display a banner
void Owner::displayBanner(){
    store.displayBanner();
}

//persist clients and inventory lists
bool Owner::save(){
    writeToClients();
    return store.writeToInventory();
}

//interaction for modifying books
bool Owner::updateABook(){
    bool done = false;
    while(!done){
        int response;
        displayInventory(false);
        cout << "which book would you like to modify? (0) to quit.\n";
        cin >> response;

        if(response == 0)
            done = true;
        else if(response > store.inventory.size() || response < 0){
            cout << "Invalid input. Please try again.\n";
        } else {
            response--; //update to inventory index
            int modify;
            cout << "Would you like to modify: \n(1)Title \n(2)Author \n(3)ISBN \n(4)Quantity \n(5) Price \n(0) Go back\n";
            cin >> modify;
            switch(modify) {
                case 0: {
                    done = true;
                    break;
                }
                //update the title
                case 1: {
                    string newTitle;
                    cout << "Current: " << store.inventory[response]->getName() << "\nNew: ";
                    cin >> newTitle;
                    store.inventory[response]->setName(newTitle);
                    cout << "Success!\n";
                    break;
                }
                //update the author
                case 2: {
                    string newAuthor;
                    cout << "Current: " << store.inventory[response]->getAuthor() << "\nNew: ";
                    cin >> newAuthor;
                    store.inventory[response]->setAuthor(newAuthor);
                    cout << "Success!\n";
                    break;
                }

                //update the isbn
                case 3: {
                    int newIsbn;
                    cout << "Current: " << to_string(store.inventory[response]->getIsbn()) << "\nNew: ";
                    cin >> newIsbn;
                    store.inventory[response]->setIsbn(newIsbn);
                    cout << "Success!\n";
                    break;
                }
                //update the stock numbers
                case 4: {
                    int  newQuantity;
                    cout << "Current: " << to_string(store.inventory[response]->getStock()) << "\nNew: ";
                    cin >> newQuantity;
                    store.inventory[response]->setStock(newQuantity);
                    cout << "Success!\n";
                    break;
                }
                //update the price
                case 5: {
                    float newPrice;
                    cout << "Current: $" << to_string(store.inventory[response]->getPrice()) << "\nNew: $";
                    cin >> newPrice;
                    store.inventory[response]->setPrice(newPrice);
                    cout << "Success!\n";
                    break;
                }
                default:
                    cout << "Invalid input. Please try again\n";
                    break;

            }
            //save
            store.writeToInventory();
        }
    }
    return true;
}

//Add a new book to the inventory
bool Owner::addABook() {
    string title, author;
    int isbn, quantity;
    float price;
    //Get details for new book
    cout <<"Title: ";
    cin.get();
    getline(cin, title);
    cout << "Author: ";
    cin.get();
    getline(cin, author);
    cin.clear();
    cout << "ISBN: ";
    cin >> isbn;
    cin.clear();
    cout << "Quantity: ";
    cin >> quantity;
    cin.clear();
    cout <<"Price: $";
    cin >> price;
    cin.clear();
    //add the book
    store.addBook(title, author, isbn, quantity, price);
    //save the inventory
    store.writeToInventory();
    return true;
}

//interaction to modify or add a book
bool Owner::modifyBooks(){
    bool done = false;
    while(!done) {
        int response;
        cout << "Would you like to:\n(1) Modify an existing book \n(2) Add a new book \n(0) Go back\n";
        cin >> response;
        switch(response) {
            case 0:
                done = true;
                break;
            case 1:
                updateABook();
                break;
            case 2:
                addABook();
                break;
            default:
                cout << "Invalid input. Please try again.\n";
                break;
        }
    }
    return true;
}

bool Owner::updateBook(int index){
    return true;
}

//display list past clients
void Owner::printClients(){
    cout << "Clients: \n";
    for(int i = 0; i < clients.size(); i++) {
        cout << "(" << i+1 << ") " << clients[i]->getName() << endl;
    }
}

//dialog to sell a book
void Owner::sellBook(int isNew){
    int bookIndex;
    displayInventory(false);
    cout << "Which book would you like to purchase? (0) to Quit\n";
    cin.clear();
    cin >> bookIndex;
    //if new, get info, add
    if(isNew) {
        string name, address;
        int cc;
        cout << "Great, now let's get your info.\n";
        cout << "Name: ";
        cin.get();
        getline(cin, name);
        cout << "Address: ";
        cin.get();
        getline(cin, address);
        cout << "Credit card: ";
        cin >> cc;
        clients.push_back(new Client(name, address, cc));
        //now sell the book
        int stock = store.inventory[bookIndex-1]->getStock();
            if(stock>0) {
                store.inventory[bookIndex-1]->setStock(stock-1);
                cout << "Purchase successful!\n";
            } else {
                cout << "Purchase failed! None remaining.\n";
                sellBook(0);
                return;
            }
    } else {
        //check past clients to get info
        if(clients.size()<1) {
            cout << "No previous clients found\n";
            sellBook(0);
            return;
        }
        //returning, retreive info
        int id;
        printClients();
        cout << "Which number is your name? (0) if not found\n";
        cin >> id;
        //sell the book
        if(id) {
            int stock = store.inventory[bookIndex-1]->getStock();
            if(stock>0) {
                store.inventory[bookIndex-1]->setStock(stock-1);
                cout << "Purchase successful!\n";
            } else {
                cout << "Purchase failed! None remaining.\n";
                sellBook(0);
                return;
            }
        }

    }
}

//read in from file
bool Owner::readToClients() {
    ifstream file("clients.csv");
    if(file.is_open()) {
        while(file.good()) {
            /*
             * Csv line should read as Name,Address,creditCardNumber
             */
            string name, address, cc;
            getline(file, name, ',');
            getline(file, address, ',');
            getline(file, cc, ',');
            //strip the newline from the file if read in
            name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());
            //cout << name << " " << author << " " << isbn << " " << quantity << " " << price << endl;
            clients.push_back(new Client(name, address, stoi(cc)));
        }
        file.close();
        return true;
    } else {
        file.close();
        return false;
    }

}

//persist to csv file
bool Owner::writeToClients(){
    ofstream file("clients.csv");
    if(file.is_open()) {
        //write clients to csv
        for(int i = 0; i < clients.size(); i++){
            string ln = clients[i]->getName() + ','
                    + clients[i]->getAddress() + ','
                    + to_string(clients[i]->getCreditCard());
            if(i+1 < clients.size()) //not the last line to write
                ln+=",\n"; //don't add more commas on the last line
            file << ln;
            //putline(file, ln);
         }
         file.close();
        return true;
    } else {
        file.close();
        return false;
    }
}

//clean up allocated memory
Owner::~Owner(){
    save();
    for(int i = 0; i < clients.size(); i++) {
        delete(clients[i]);
    }
}
