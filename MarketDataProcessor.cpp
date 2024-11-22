#include "MarketDataProcessor.h"

void MarketDataProcessor::addTick(const MarketTick& tick)
{
	m_TickMap[tick.getSymbol()].insert(tick);
}

std::vector<std::string> MarketDataProcessor::returnStat(int stepsNum)	// Iterates through containter of MarketTicks and creates a string with calculated statistics per symbol.
{																		// If there is no data for a specific statistic, shows "No data" in corresponding field
	std::vector<std::string> stat;
	for (auto& x : m_TickMap)
	{
		std::string VWAP, SMA, highestPrice, lowestPrice;

		std::pair<double, bool> result = calculateVWAP(x.first); // First value holds the statistics, second value shows if the data exists (result.second = false means there is no usable data)
		VWAP = result.second ? std::to_string(result.first) : "No data";

		result = calculateSMA(x.first, stepsNum);
		SMA = result.second ? std::to_string(result.first) : "No data";

		try
		{
			result = calculateHighestPrice(x.first);
			highestPrice = result.second ? std::to_string(result.first) : "No data";
		}
		catch (const std::exception& ex)
		{
			std::cerr << "Error: " << ex.what() << "\n";
			highestPrice = "ERROR";								//Will show error instead of value in the stats if the exception was thrown by method
		}

		try
		{
			result = calculateLowestPrice(x.first);
			lowestPrice = result.second ? std::to_string(result.first) : "No data";
		}
		catch (const std::exception& ex)
		{
			std::cerr << "Error: " << ex.what() << "\n";
			lowestPrice = "ERROR";
		}
		// Creates a string of stats.
		std::string row = x.first + "\t" + "VWAP:" + VWAP + "\t" + "SMA:" + SMA + "\t" + "Highest:" + highestPrice + "\t" + "Lowest:" + lowestPrice;

		stat.push_back(row);
	}

	return stat;
}

std::pair<double, bool> MarketDataProcessor::calculateVWAP(const std::string& symbol)
{
	double totalCost = 0;
	int volume = 0;
	for (const MarketTick& x : m_TickMap[symbol])
	{
		totalCost += (x.getPrice() * x.getVolume());
		volume += x.getVolume();
	}

	std::pair<double, bool> result;  // result.second shows if the result is valid
	if (volume == 0) result = { 0, false};
	else result = { totalCost / volume, true};

	return result;
}

std::pair<double, bool> MarketDataProcessor::calculateSMA(const std::string& symbol, int n = 3) // Assumption: if n is lower than number of elements, SMA of lower number of elements will be returned
{
	std::set<MarketTick>::iterator iter = m_TickMap[symbol].begin();
	double sum = 0;
	int i;
	for (i = 0; i < n && iter != m_TickMap[symbol].end(); ++iter, ++i)
	{
		sum += iter->getPrice();
	}

	std::pair<double, bool> result; // result.second shows if the result is valid
	if (i == 0) result = { 0, false };
	else result = { sum / i, true };

	return result;
}

std::pair<double, bool> MarketDataProcessor::calculateLowestPrice(const std::string& symbol, uint64_t start, uint64_t end)
{
	std::set<MarketTick>::iterator iter = m_TickMap[symbol].begin();
	if (start > end) throw std::runtime_error("Incorrect time in calculating lowest price"); // Throws exception if timeframe is invalid

	double lowest = DBL_MAX;
	bool dataFound = false;

	for (;iter != m_TickMap[symbol].end() && iter->getTimestamp() > start; ++iter) // Simply iterates through array to find lowest Price
	{
		if (iter->getTimestamp() > end) continue;
		else
		{
			if (lowest > iter->getPrice()) lowest = iter->getPrice();
			dataFound = true;
		}
	}

	std::pair<double, bool> result = { lowest, dataFound }; // result.second shows if the result is valid
	return result;
}

std::pair<double, bool> MarketDataProcessor::calculateHighestPrice(const std::string& symbol, uint64_t start, uint64_t end)
{
	std::set<MarketTick>::iterator iter = m_TickMap[symbol].begin();
	if (start > end) throw std::runtime_error("Incorrect time in calculating lowest price"); // Throws exception if timeframe is invalid

	double highest = 0;
	bool dataFound = false;

	for (; iter != m_TickMap[symbol].end() && iter->getTimestamp() > start; ++iter)
	{
		if (iter->getTimestamp() > end) continue;
		else
		{
			if (highest < iter->getPrice()) highest = iter->getPrice();
			dataFound = true;
		}
	}

	std::pair<double, bool> result = { highest, dataFound }; // result.second shows if the result is valid
	return result;
}
