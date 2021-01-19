#include <iostream>
#include <fstream>
#include <cstring>
#include <thread>

using namespace std;

// Parmameters make up the range the threads will be supplied with. Along with an array that will be edited.
void calculatePrimes(int* primes, int start, int end)
{
    if(start < 2)
        start = 2;

    for(int i = start; (i * i) <= end; i++)
    {
        cout << i << endl;
        if(primes[i] == 1)
        {

            for(int j = (i*i); j <= end; j += i)
            {
                primes[j] = 0;
            }

        }

    }

}

void DoTheStuff()
{
    for(int i = 0; i < 5; i++)
    {
        cout << i << ", ";
        cout << "This is thread: " << this_thread::get_id() << endl; 
    }
}


int main()
{
    ofstream myFile;
    myFile.open("output.txt", ios::out);

    int n = 100;
    int* primes = new int[n + 1];
    
    for(int i = 0; i < n + 1; i++)
    {
        primes[i] = 1;
    }

    thread t1(DoTheStuff);
    thread t2(DoTheStuff);
    thread t3(DoTheStuff);
    
    t1.join();
    t2.join();
    t3.join();

    // Label all numbers as prime, as later composite numbers will be marked, where 1 is prime, and 0 is composite.
    // for(int i = 0; i < n; i++)
    // {
    //     primes[i] = 1;
    // }
    
    // Each thread will essentially be given a range of numbers to calculate independently
    // So by supplying the range to those functions and utilizing the isPrime function. They will be marked appropriately and then the sum and such can be found.    

    //calculatePrimes(primes, 0, n);
    
    // for(int i = 2; i <= 100; i++)
    //     if(primes[i] == 1)
    //     {            
    //         myFile << i << endl;  
    //     } 


    try
    {
        if(!myFile.is_open())
            throw "Output file is not open, and therefore can't be written to.";

    }
    catch(const char* message)
    {
        cerr << message << endl;
    }

    cout << endl;

    myFile.close();

}
