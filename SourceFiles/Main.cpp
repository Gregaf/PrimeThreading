#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <thread>
#include <atomic>

using namespace std::chrono;

using std::cout;
using std::endl;

#define NUMBER_OF_THREADS 8

std::atomic<int> counter;
std::atomic<int> primeCount;

// Given a number, checks whether it is prime.
bool isPrime(int n)
{
    // 0 and 1 are not prime.
    if(n < 2)
        return false;
    // 2 is the only even prime.
    else if(n == 2)
        return true;
    // n must be even which means that n can't be prime.
    else if(n % 2 == 0) 
        return false;

    if(n % 2 == 0 || n % 3 == 0)
        return false;

    for(int i = 5; (i*i) <= n; i +=6)
    {
        if(n % i == 0 || n % (i + 2) == 0)
            return false;
    }

    return true;
}

void calculatePrimes(int* primes, int end)
{
    while(counter < end)
    {
        if(!isPrime(counter))
        {
            primes[counter] = 0;

        }
        else
            primeCount++;

        counter++;
    }
    

}



int main()
{
    std::ofstream myFile;
    myFile.open("output.txt", std::ios::out);
    std::vector<std::thread> threads;

    int n = 100000000;
    int* primes = new int[n + 1];
    
    // Intialize all numbers to be considered prime, so we can set them not prime as we go through.
    for(int i = 0; i < n + 1; i++)
    {
        primes[i] = 1;
    }
        
    auto start = high_resolution_clock::now();
    
#pragma region Single Thread Execution
    counter = 1;

    calculatePrimes(primes, n);

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start);
    
    cout << "Time taken with singlethreaded: " << (duration.count()) << " miliseconds." << endl;

#pragma endregion


#pragma region Multithreaded Execution
    start = high_resolution_clock::now();
    
    counter = 1;

    // Spawn the threads.
    for(int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        threads.push_back(std::thread(calculatePrimes, primes, n));

    }
        
    // Iterate over each thread and join them to the main thread.
    for(auto& thread : threads)
    {
        thread.join();
    }

    stop = high_resolution_clock::now();

    duration = duration_cast<milliseconds>(stop - start);
    
    cout << "Time taken with multithreading: " << (duration.count()) << " miliseconds." << endl;
#pragma endregion

    cout << primeCount << endl;

    try
    {
        if(!myFile.is_open())
            throw "Output file is not open, and therefore can't be written to.";

        myFile << '<' << duration.count() << "> ";

        int i = n;
        int maxPrimeCount = 0;

        myFile<< '<';

        while(maxPrimeCount < 10)
        {
            if(primes[i] == 1)
            {
                myFile << i << ", ";
                maxPrimeCount++;
            }

            i--;
        }

        myFile << '>' << endl;

        // myFile << '<' << totalPrimes << '> ';
        // myFile << '<' << sumOfPrimes << '> ';
        // myFile << '<' << maxPrimes << '> ';
    }
    catch(const char* message)
    {
        std::cerr << message << endl;
    }

    cout << endl;

    myFile.close();

}
