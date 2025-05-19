#include <iostream>
#include <string>

using namespace std;

int main()
{
    cout << "Welcome to the Online examination system" << endl;
    cout << "Please enter your name: ";
    string name;
    cin >> name;
    cout << "Hello " << name << ", Who you are?" << endl;
    cout << "1. Student" << endl;
    cout << "2. Teacher" << endl;
    cout << "3. Admin" << endl;
    cout << "Please enter your choice: ";
    system("pause");
    cout << "Thank you for your choice" << endl;
    return 0;
}