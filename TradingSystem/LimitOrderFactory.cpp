#include "LimitOrderFactory.h"

Order LimitOrderFactory::createOrder(std::string traderName, std::string stockSymbol, int quantity, double price) {
    return Order(traderName, stockSymbol, Order::OrderType::Limit, quantity, price);
}