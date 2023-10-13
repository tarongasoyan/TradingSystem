#include "Order.h"

Order::Order(std::string traderName, std::string stockSymbol, OrderType type, int quantity, double price)
    : traderName(traderName), stockSymbol(stockSymbol), type(type), quantity(quantity), price(price) {}

std::string Order::getTraderName() const {
    return traderName;
}

std::string Order::getStockSymbol() const {
    return stockSymbol;
}

Order::OrderType Order::getOrderType() const {
    return type;
}

int Order::getQuantity() const {
    return quantity;
}

void Order::setQuantity(int newQuantity)
{
    quantity = newQuantity;
}

double Order::getPrice() const {
    return price;
}

double Order::getTotalCost() const
{
    if (orderType == OrderType::Market) {
        return quantity * price;
    }
    else if (orderType == OrderType::Limit) {
        return (quantity > 0) ? (quantity * price) : 0.0; 
    }
}

std::string Order::toString() const
{
    std::string orderTypeName = (orderType == OrderType::Market) ? "Market" : "Limit";
    std::string orderDirection = (quantity > 0) ? "Buy" : "Sell";

    return orderDirection + " " + orderTypeName + " order: " +
        std::to_string(abs(quantity)) + " shares of " + stockSymbol +
        " at $" + std::to_string(price);
}