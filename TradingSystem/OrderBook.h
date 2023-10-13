#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <vector>
#include "Order.h"
#include "Observer.h"
#include <mutex>

class OrderBook : public Observer {
public:
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
    void update(const std::string& message) override;
    void addOrder(const Order& order);
    void matchOrders();
    void stopTrading();
    bool isTrading() const;
private:
    std::vector<Order> buyOrders;
    std::vector<Order> sellOrders;
    std::vector<Observer*> observers;
    bool tradingActive = true;
    std::mutex orderMutex;
private:
    void executeMarketOrder(const Order& marketOrder);
    void executeLimitOrder(const Order& limitOrder);
    bool canExecute(const Order& buyOrder, const Order& sellOrder);
    void executeTrade(const Order& buyOrder, const Order& sellOrder);
    void notifyObservers(const std::string& message);
};

#endif