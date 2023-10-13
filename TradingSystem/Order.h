#ifndef ORDER_H
#define ORDER_H

#include <string>

class Order {
public:
    enum class OrderType { Market, Limit };

    Order(std::string traderName, std::string stockSymbol, OrderType type, int quantity, double price);
    std::string getTraderName() const;
    std::string getStockSymbol() const;
    OrderType getOrderType() const;
    int getQuantity() const;
    void setQuantity(int newQuantity);
    double getPrice() const;
    double getTotalCost() const;
    std::string toString() const;
private:
    OrderType orderType;
    std::string traderName;
    std::string stockSymbol;
    OrderType type;
    int quantity;
    double price;
};

#endif