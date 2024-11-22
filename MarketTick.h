#pragma once
#include <string>
#include <cstdint>
#include <stdexcept>

class MarketTick
{
private:
    std::string m_symbol;     // Stock symbol like "AAPL" (max 20 chars)
    double m_price;      // Current price, e.g., 150.25
    int m_volume;        // Number of shares traded
    uint64_t m_timestamp; // When this happened (Unix timestamp in seconds)

public:
    // Constructor - create a new market tick
    MarketTick(std::string symbol, double price, int volume, uint64_t timestamp);

    static void validateSymbol(const std::string& symbol);
    static void validatePrice(double price);
    static void validateVolume(int volume);
    //static void validateTimestamp(uint64_t timestamp);

    //Getters
    const std::string& getSymbol() const;
    double getPrice() const;
    int getVolume() const;
    uint64_t getTimestamp() const;

    // Setters
    void setSymbol(std::string symbol);
    void setPrice(double price);
    void setVolume(int volume);
    void setTimestamp(uint64_t timestamp);

    bool operator<(const MarketTick& other) const;
    bool operator>(const MarketTick& other) const;


};




