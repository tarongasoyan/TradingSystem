#ifndef MARKET_ORDER_FACTORY_H
#define MARKET_ORDER_FACTORY_H

#include "OrderFactory.h"

class MarketOrderFactory : public OrderFactory {
public:
    Order createOrder(std::string traderName, std::string stockSymbol, int quantity, double price) override;
};

#endif