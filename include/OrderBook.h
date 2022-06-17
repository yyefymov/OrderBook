#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <map>
#include <vector>
#include <memory>
#include "Order.h"

class OrderBook
{
public:
    using bucket_type =  std::map< unsigned int, std::shared_ptr<Order> >;

    OrderBook() = default;
    ~OrderBook() = default;

    // This is a new order added to the book; it will have a new/unique order-id.
    void insert(const std::shared_ptr<Order>& order);

    // The order with the given order-id is to be changed to the new volume and/or price.
    void cancel(unsigned int orderID);

    // The order with the given order-id is to be changed to the new volume and/or price.
    void amend(unsigned int orderID, unsigned int volume, double price);

    // Given the order id, returns read-only reference to a corresponding order (or null if none found)
    std::shared_ptr<const Order> getOrder(unsigned int orderID);

    // Counts the total number of orders per symbol.
    std::map<std::string, unsigned int> orderCounts() const;

    // Finds the top 3 biggest BUY orders in terms of volume for a specific symbol.
    std::vector< std::shared_ptr<const Order> > biggestBuyOrders(const std::string& symbol) const;

    // Finds the best SELL price and related order volume for a specific symbol at a given time.
    std::shared_ptr<const Order> bestSellAtTime(const std::string& symbol, const CustomTypes::timestamp& timestamp) const;

private:
    std::map<std::string, bucket_type> orders;

};

#endif // ORDERBOOK_H
