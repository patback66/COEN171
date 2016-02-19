#include "book.h"
#include "person.h"
#include "owner.h"
#include "client.h"
#include "store.h"
#include "iostream"

using namespace std;

Owner me;// = new Owner("Matthew Koken");

void ownerRoutine();
void clientRoutine();

int main(int argc, char *argv[])
{
    bool done = false;
    //Owner me = new Owner("Matthew Koken");
    //QGuiApplication app(argc, argv);

    //QQmlApplicationEngine engine;
    //engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    me.displayBanner();
    while(!done){
        int response;
        cout << "(0) to quit.\n";
        cout << "Are you the (1) Owner or (2) Client? ";
        cin.clear();
        cin >> response;

        switch(response) {
            case 0:
                done = true;
                break;
            case 1:
                ownerRoutine();
                break;
            case 2:
                clientRoutine();
                break;
            default:
                cout << "Invalid response. Please try again.\n";
                break;
        }

        //update price
        //print inventory

        //select books
        //add personal info
        //buy books

        //save info
    }
    //save the store before closing
    cout << "Saving" << endl;
    me.save();
    cout << "Saved" << endl;


    //return app.exec();
    return 0;
}

void ownerRoutine(){
    bool done = false;
    while(!done) {
        int response;
        cout << "Options: (1) Show Options (2) Display inventory (3) Update a book (0) Quit\n";
        cin.clear();
        cin >> response;
        switch(response){
            case 0:
                done = true;
                break;
            case 1:
                break;
            case 2:
                me.displayInventory(false);
                break;
            case 3:
                me.modifyBooks();
                break;
            default:
                cout << "Invalid response. Please try again.\n";
                break;
        }
    }
}

//Gives client instructions
void clientRoutine(){
    bool done = false;
    int isNew;
    cout << "Hello, are you a (1)new or (2)returning customer? (0) to quit. ";
    cin >> isNew;

    while(!done) {
        me.displayInventory(true);
        int response;

        cout << "Options: \n(1) Buy a book \n(2) Display inventory \n(0) Quit\n";
        cin.clear();
        cin >> response;
        switch(response) {
            case 0:
                done = true;
                break;
            case 1: {
                me.sellBook(isNew);
                break;
            }
            default:
                cout << "Invalid input. Please try again.\n";
                break;
        }
    }

}
