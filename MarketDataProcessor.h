#pragma once
#include "MarketTick.h"
#include <unordered_map>
#include <cstdint>
#include <iostream>
#include <cfloat>
#include <set>
#include <vector>
class MarketDataProcessor {

private:
    std::unordered_map<std::string, std::set<MarketTick>> m_TickMap;
public:
    // Add a new price update
    void addTick(const MarketTick& tick);
    
    //Returns statistics for every symbol, one string per symbol
    std::vector<std::string> returnStat(int stepsNum = 3);

    // Calculate VWAP for a symbol
    std::pair<double, bool> calculateVWAP(const std::string& symbol);

    // Calculate moving average
    std::pair<double, bool> calculateSMA(const std::string& symbol, int n);

    // Calculate lowest and highest prices
    std::pair<double, bool> calculateLowestPrice(const std::string& symbol, uint64_t start = 0, uint64_t end = UINT64_MAX);
    std::pair<double, bool> calculateHighestPrice(const std::string& symbol, uint64_t start = 0, uint64_t end = UINT64_MAX);
};

