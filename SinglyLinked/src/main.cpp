#include <iostream>
#include <string>
#include "SinglyLinked.h"
using namespace std;

struct User
{
    string name;
    int age;
};

int main()
{
    SList<User> *L = new SList<User>[2];
    User u1 = {"name1", 23};
    L[0].addFront(u1);
    User u2 = {"name2", 27};
    L[1].addFront(u2);
    cout << L[0].getFront().name << " " << L[0].getFront().age << endl;
    cout << L[1].getFront().name << " " << L[1].getFront().age << endl;
    delete[] L;
    return 0;
}