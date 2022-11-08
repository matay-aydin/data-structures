#include <iostream>
#include <string>
#include "DoublyLinked.h"
using namespace std;

int main()
{
    DList<string> D;
    D.addFront("A");
    D.addBack("B");
    D.addBack("C");
    if (D.hasData("C"))
    {
        cout << "D has C" << endl;
    }
    cout << D.getSize() << endl;
    cout << D.getFront() << endl;
    cout << D.getBack() << endl;
    D.delFront();
    cout << D.getSize() << endl;
    cout << D.getFront() << endl;
    D.delBack();
    cout << D.getSize() << endl;
    cout << D.getBack() << endl;
    D.delBack();
    try
    {
        D.delFront();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}