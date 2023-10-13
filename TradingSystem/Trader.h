#ifndef TRADER_H
#define TRADER_H

#include <string>
#include <vector>
#include "Order.h"
#include "Observer.h"

class Trader : public Observer {
public:
    Trader(int id, std::string name, double balance);
public:
    int getID() const;
    double getBalance() const;
    std::string getName() const;
public:
    void addObserver(Trader* observer);
    void removeObserver(Trader* observer);
    void update(const std::string& message) override;
    void buyStock(std::string symbol, int quantity, double price);
    void sellStock(std::string symbol, int quantity, double price);
    void placeOrder(const std::string& stockSymbol, Order::OrderType orderType, int quantity, double price);
    void startTrading();
    void stopTrading();
    bool isTrading() const;
private:
    int id;
    std::string name;
    double balance;
    std::vector<std::string> portfolio;
    std::vector<Trader*> observers;
    bool tradingActive;
};

#endif