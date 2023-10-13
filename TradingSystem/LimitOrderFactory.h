#ifndef LIMIT_ORDER_FACTORY_H
#define LIMIT_ORDER_FACTORY_H

#include "OrderFactory.h"

class LimitOrderFactory : public OrderFactory {
public:
    Order createOrder(std::string traderName, std::string stockSymbol, int quantity, double price) override;
};

#endif