#include "MarketTick.h"
#include <stdexcept>

MarketTick::MarketTick(std::string symbol, double price, int volume, uint64_t timestamp) : m_symbol(symbol), m_price(price), m_volume(volume), m_timestamp(timestamp)
{
	validateSymbol(symbol);
	validatePrice(price);
	validateVolume(volume);
}

void MarketTick::validateSymbol(const std::string& symbol)
{
	if (symbol.length() > 20 || symbol.empty()) throw std::invalid_argument("Incorrect symbol value");
}

void MarketTick::validatePrice(double price)
{
	if (price < 0) throw std::invalid_argument("Incorrect price value");
}

void MarketTick::validateVolume(int volume) // Assumes that volume = 0 is incorrect
{
	if (volume <= 0) throw std::invalid_argument("Incorrect volume value");
}

//void MarketTick::validateTimestamp(uint64_t timestamp) //
//{
//	return;
//}

const std::string& MarketTick::getSymbol() const
{
	return m_symbol;
}

double MarketTick::getPrice() const
{
	return m_price;
}

int MarketTick::getVolume() const
{
	return m_volume;
}

uint64_t MarketTick::getTimestamp() const
{
	return m_timestamp;
}

void MarketTick::setSymbol(std::string symbol)
{
	validateSymbol(symbol);
	m_symbol = symbol;
}

void MarketTick::setPrice(double price)
{
	validatePrice(price);
	m_price = price;
}

void MarketTick::setVolume(int volume)
{
	validateVolume(volume);
	m_volume = volume;
}

void MarketTick::setTimestamp(uint64_t timestamp)
{
	m_timestamp = timestamp;
}

bool MarketTick::operator<(const MarketTick& other) const // Returns inverse answer so what std::set has the latest timestamps first
{
	const uint64_t a = m_timestamp;
	return this->m_timestamp > other.m_timestamp;
}

bool MarketTick::operator>(const MarketTick& other) const // Returns inverse answer, is not utilized
{
	return this->m_timestamp < other.m_timestamp;
}
