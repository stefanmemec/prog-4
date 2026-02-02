#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    char ch;
    fstream fin("../test.txt", fstream::in);
    while (fin >> noskipws >> ch) {
        cout << ch; // Or whatever
    }
}