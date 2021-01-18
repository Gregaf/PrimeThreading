#include <iostream>
#include <fstream>
#include <string>
#include "../HeaderFiles/PrimeNumbers.h"

using namespace std;

int main()
{
    ofstream myFile;
    myFile.open("output.txt", ios::out);
    

    cout << "Hello World!" << endl;
    
    int sum = 0;

    for(int i = 0; i < 100; i++)
    {
        sum += i;
    }   

    try
    {
        if(!myFile.is_open())
            throw "Output file is not open, and therefore can't be written to.";

        myFile << '<' << sum << '>';
        
    }
    catch(const char* message)
    {
        cerr << message << endl;
    }

    cout << endl;

    myFile.close();
}

    