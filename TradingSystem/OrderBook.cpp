#include "OrderBook.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <mutex>

void OrderBook::addObserver(Observer* observer) {
    observers.push_back(observer);
}

void OrderBook::removeObserver(Observer* observer) {
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end()) {
        observers.erase(it);
    }
}

void OrderBook::update(const std::string& message) {
    std::cout << "OrderBook received a message: " << message << "\n";
}

void OrderBook::addOrder(const Order& order) {
    if (order.getOrderType() == Order::OrderType::Market) {
        std::string message = "Market order for " + std::to_string(order.getQuantity()) + " shares of " + order.getStockSymbol() + ".";
        std::cout << message << "\n";
        for (Observer* observer : observers) {
            observer->update(message);
        }
    }
    else {
        if (order.getQuantity() > 0) {
            buyOrders.push_back(order);
            std::string message = "Added buy order for " + std::to_string(order.getQuantity()) + " shares of " + order.getStockSymbol() + " at $" + std::to_string(order.getPrice()) + " each.";
            std::cout << message << "\n";
            for (Observer* observer : observers) {
                observer->update(message);
            }
        }
        else {
            sellOrders.push_back(order);
            std::string message = "Added sell order for " + std::to_string(-order.getQuantity()) + " shares of " + order.getStockSymbol() + " at $" + std::to_string(order.getPrice()) + " each.";
            std::cout << message << "\n";
            for (Observer* observer : observers) {
                observer->update(message);
            }
        }
    }
}

bool OrderBook::canExecute(const Order& buyOrder, const Order& sellOrder) {
    return (buyOrder.getStockSymbol() == sellOrder.getStockSymbol() &&
        buyOrder.getPrice() >= sellOrder.getPrice() &&
        buyOrder.getQuantity() >= sellOrder.getQuantity());
}

void OrderBook::executeTrade(const Order& buyOrder, const Order& sellOrder) {
    double totalPrice = sellOrder.getPrice() * sellOrder.getQuantity();
    std::string tradeMessage = "Trade executed: " + buyOrder.getTraderName() + " bought " + std::to_string(buyOrder.getQuantity()) +
        " shares from " + sellOrder.getTraderName() + " for $" + std::to_string(totalPrice);
    std::cout << tradeMessage << std::endl;
    for (Observer* observer : observers) {
        observer->update(tradeMessage);
    }
}

void OrderBook::notifyObservers(const std::string& message)
{
    for (Observer* observer : observers) {
        observer->update(message);
    }
}

void OrderBook::stopTrading() {
    tradingActive = false;
}

bool OrderBook::isTrading() const
{
    return tradingActive;
}

void OrderBook::executeMarketOrder(const Order& marketOrder) {
    std::lock_guard<std::mutex> lock(orderMutex);

    for (auto it = sellOrders.begin(); it != sellOrders.end();) {
        if (marketOrder.getQuantity() > 0 && marketOrder.getStockSymbol() == it->getStockSymbol()) {
            if (marketOrder.getQuantity() >= it->getQuantity()) {
                executeTrade(marketOrder, *it);
                it = sellOrders.erase(it);
            }
            else {
                executeTrade(marketOrder, *it);
                it->setQuantity(it->getQuantity() - marketOrder.getQuantity());
            }
        }
        else {
            ++it;
        }
    }
}

void OrderBook::executeLimitOrder(const Order& limitOrder) {
    std::lock_guard<std::mutex> lock(orderMutex);
    for (auto it = buyOrders.begin(); it != buyOrders.end();) {
        if (limitOrder.getQuantity() > 0 && limitOrder.getStockSymbol() == it->getStockSymbol() &&
            limitOrder.getPrice() >= it->getPrice()) {
            if (limitOrder.getQuantity() >= it->getQuantity()) {
                executeTrade(*it, limitOrder);
                it = buyOrders.erase(it);
            }
            else {
                executeTrade(*it, limitOrder);
                it->setQuantity(it->getQuantity() - limitOrder.getQuantity());
                it = buyOrders.erase(it);
            }
        }
        else {
            ++it;
        }
    }
    if (limitOrder.getQuantity() > 0) {
        buyOrders.push_back(limitOrder);
    }
}


void OrderBook::matchOrders() {
    while (tradingActive) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        {
            std::lock_guard<std::mutex> lock(orderMutex);
      
            if (!buyOrders.empty() && !sellOrders.empty()) {
                Order buyOrder = buyOrders.front();
                Order sellOrder = sellOrders.front();

                if (canExecute(buyOrder, sellOrder)) {
                    executeTrade(buyOrder, sellOrder);

                    buyOrders.erase(buyOrders.begin());
                    sellOrders.erase(sellOrders.begin());
                }
            }
        }
    }
}