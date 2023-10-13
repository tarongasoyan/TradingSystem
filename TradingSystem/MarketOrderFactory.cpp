#include "MarketOrderFactory.h"

Order MarketOrderFactory::createOrder(std::string traderName, std::string stockSymbol, int quantity, double price) {
    return Order(traderName, stockSymbol, Order::OrderType::Market, quantity, price);
}