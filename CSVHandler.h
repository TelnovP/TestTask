#pragma once
#include <string>
#include <iostream>
#include "MarketDataProcessor.h"
#include <fstream>
#include <sstream>
class CSVHandler
{
public:
	void readFile(std::string filename, MarketDataProcessor& obj);

	void writeFile(std::string filename, MarketDataProcessor& obj);
};

