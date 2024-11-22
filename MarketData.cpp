// MarketData.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include "MarketDataProcessor.h"
#include "CSVHandler.h"

int main()
{
    auto start = std::chrono::steady_clock::now();

    MarketDataProcessor a;
    CSVHandler csv;
    try
    {      
        csv.readFile("dataFile.csv", a);

        csv.writeFile("outFile.txt", a);
    }
    catch (const std::exception& ex) 
    {
        std::cerr << "Error: " << ex.what() << "\n";
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> time = end - start; // Gets execution time
    std::cout << "Execution time: " << time.count() << " ms" << std::endl;
    return 0;   
}
