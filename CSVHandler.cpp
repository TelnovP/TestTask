#include "CSVHandler.h"

void CSVHandler::readFile(std::string filename, MarketDataProcessor& obj)
{
	std::fstream fin;
	fin.open(filename);
	if (!fin.is_open()) throw std::runtime_error("Could not open file");

	std::string line, word;
	std::vector<std::string> row;
	while (fin.good()) // Reads the file line by line
	{
		row.clear();
		std::getline(fin, line);
		std::stringstream ss(line);

		while (std::getline(ss, word, ','))
		{
			row.push_back(word); //Stores the elements from line separetely as strings
		}
		try
		{
			if (row.size()<4) throw std::runtime_error("Incorrect data read from file."); // Not enough data was found to create a MarketTick
			if (stoll(row[3]) < 0) throw std::runtime_error("Incorrect time data found while reading file"); // While negative values can be used because of the wrap around, they might result in confusion later on
			obj.addTick(MarketTick(row[0], stod(row[1]), stoi(row[2]), stoull(row[3])));
		}
		catch (const std::exception& ex)
		{
			std::cerr << "Error: " << ex.what() << "\n";
		}
	}
	fin.close();
}

void CSVHandler::writeFile(std::string filename, MarketDataProcessor& obj)
{
	std::ofstream fout(filename);

	std::vector<std::string> sList = obj.returnStat();

	for (std::string& x : sList)
	{
		fout << x << std::endl;
	}

	fout.close();
}


