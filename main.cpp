#include <iostream>
#include "rbtree.h"
#include "rbtree.cpp"

using namespace std;

int main()
{
    TreeType<int> T1;
    int value_for_operation;
    char tree_operation;

    cout << "Enter I to insert a value, or D to delete a value. Enter P to print the tree. Enter X to exit the tree.\n";
    cin >> tree_operation;

    while (tree_operation != 'X') {
        switch (tree_operation) {
            case 'I':
                cout << "Input the value to insert:\n";
                cin >> value_for_operation;
                T1.InsertItem(value_for_operation);
                break;
            case 'D':
                cout << "Input the value to delete:\n";
                cin >> value_for_operation;
                T1.DeleteItem(value_for_operation);
                break;
            case 'P':
                cout << "Printing Data in list:\n";
                T1.Print();
                cout << "\n";
                break;
            case 'X':
                tree_operation = 'X';
                break;
        }
        cout << "Enter I to insert a value, or D to delete a value. Enter P to print the tree. Enter X to exit the tree.\n";
        cin >> tree_operation;
    }

    cout << "Exiting Program." << endl;
    return 0;
}
