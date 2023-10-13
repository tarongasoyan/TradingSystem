#include "Stock.h"

Stock::Stock(std::string symbol, double price)
    : symbol(symbol), price(price) {}

std::string Stock::getSymbol() const {
    return symbol;
}

double Stock::getPrice() const {
    return price;
}
