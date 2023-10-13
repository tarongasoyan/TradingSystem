#include "Trader.h"
#include <iostream>
#include "OrderBook.h"

Trader::Trader(int id, std::string name, double balance)
    : id(id), name(name), balance(balance) {}

int Trader::getID() const {
    return id;
}

double Trader::getBalance() const {
    return balance;
}

std::string Trader::getName() const {
    return name;
}

void Trader::addObserver(Trader* observer) {
    observers.push_back(observer);
}

void Trader::removeObserver(Trader* observer) {
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end()) {
        observers.erase(it);
    }
}

void Trader::update(const std::string& message) {
    std::cout << name << " received a message: " << message << "\n";
}

void Trader::buyStock(std::string symbol, int quantity, double price) {
    double totalCost = quantity * price;
    if (totalCost <= balance) {
        balance -= totalCost;
        portfolio.push_back(symbol);
        std::string message = "Bought " + std::to_string(quantity) + " shares of " + symbol + " at $" + std::to_string(price) + " each.";
        std::cout << message << "\n";
        for (Trader* observer : observers) {
            observer->update(message);
        }
    }
    else {
        std::cout << "Insufficient balance to buy " << symbol << ".\n";
    }
}

void Trader::sellStock(std::string symbol, int quantity, double price) {
    auto it = std::find(portfolio.begin(), portfolio.end(), symbol);
    if (it != portfolio.end()) {
        balance += quantity * price;
        portfolio.erase(it);
        std::string message = "Sold " + std::to_string(quantity) + " shares of " + symbol + " at $" + std::to_string(price) + " each.";
        std::cout << message << "\n";
        for (Trader* observer : observers) {
            observer->update(message);
        }
    }
    else {
        std::cout << "You do not own any shares of " << symbol << ".\n";
    }
}

void Trader::placeOrder(const std::string& stockSymbol, Order::OrderType orderType, int quantity, double price) {
    Order order(name, stockSymbol, orderType, quantity, price);
    if (orderType == Order::OrderType::Limit && order.getTotalCost() > balance) {
        std::cout << "Insufficient funds to place the order: " << order.toString() << "\n";
        return;
    }
    if (orderType == Order::OrderType::Limit) {
        balance -= order.getTotalCost();
        std::cout << "Placed limit order: " << order.toString() << "\n";
    }
    else if (orderType == Order::OrderType::Market) {
        double executedPrice = price;
        balance -= (quantity * executedPrice);
        std::cout << "Placed market order: " << order.toString() << "\n";
    }

    std::string message = "Placed order: " + order.toString();
}

void Trader::startTrading()
{
    tradingActive = true;
}

void Trader::stopTrading()
{
    tradingActive = false;
}

bool Trader::isTrading() const
{
    return tradingActive;
}