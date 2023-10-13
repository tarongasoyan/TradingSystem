#ifndef ORDER_FACTORY_H
#define ORDER_FACTORY_H

#include "Order.h"

class OrderFactory {
public:
    virtual Order createOrder(std::string traderName, std::string stockSymbol, int quantity, double price) = 0;
};

#endif