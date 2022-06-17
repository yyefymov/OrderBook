#include "include/OrderBook.h"
#include <algorithm>
#include <iostream>

constexpr unsigned short TOP_BUY_COUNT = 3;

void OrderBook::insert(const std::shared_ptr<Order> &order)
{
    if (order == nullptr)
        return;

    if (getOrder(order->getID()))
        return;

    auto& bucket = orders[order->getSymbol()];
    bucket[order->getID()] = order;
}

void OrderBook::cancel(unsigned int orderID)
{
    for (auto& kv: orders)
        kv.second.erase(orderID);
}

void OrderBook::amend(unsigned int orderID, unsigned int volume, double price)
{
    for (auto& kv: orders)
        if (kv.second.count(orderID))
        {
            kv.second[orderID]->setVolume(volume);
            kv.second[orderID]->setPrice(price);
            return;
        }
}

std::shared_ptr<const Order> OrderBook::getOrder(unsigned int orderID)
{
    for (auto& kv: orders)
        if (kv.second.count(orderID))
            return kv.second[orderID];
    return nullptr;
}

std::map<std::string, unsigned int> OrderBook::orderCounts() const
{
    std::map<std::string, unsigned int> result;

    for (const auto& kv: orders)
        result[kv.first] = kv.second.size();

    return result;
}

std::vector< std::shared_ptr<const Order> > OrderBook::biggestBuyOrders(const std::string& symbol) const
{
    try
    {
        auto& ordersBySymbol = orders.at(symbol);
        std::vector< std::shared_ptr<const Order> > buyOrders(0);
        buyOrders.reserve(TOP_BUY_COUNT); // at least

        for (const auto& kv: ordersBySymbol)
            if (kv.second->getSide() == Order::BUY)
                buyOrders.emplace_back(kv.second);

        if (buyOrders.size() < TOP_BUY_COUNT)
            return buyOrders;

        std::partial_sort(buyOrders.begin(), buyOrders.begin() + TOP_BUY_COUNT,
                          buyOrders.end(), [](const auto& order1, const auto& order2)
                                            {return order1->getVolume() > order2->getVolume();}
        );

        return std::vector< std::shared_ptr<const Order> >(buyOrders.begin(), buyOrders.begin()+TOP_BUY_COUNT);
    }
    catch(std::out_of_range)
    {
        // no order with such symbol
        return std::vector< std::shared_ptr<const Order> >();
    }
}

std::shared_ptr<const Order> OrderBook::bestSellAtTime(const std::string& symbol, const CustomTypes::timestamp& timestamp) const
{
    try
    {
        auto& ordersBySymbol = orders.at(symbol);
        std::shared_ptr<Order> maxOrder = nullptr;

        if (ordersBySymbol.empty())
            return nullptr;

        auto max = [&maxOrder, &timestamp](const auto& order)
        {
            decltype(auto) order_tm = order->getTimestamp();

            if (order_tm.tm_hour > timestamp.tm_hour)
                return;
            else if (order_tm.tm_hour == timestamp.tm_hour)
            {
                if (order_tm.tm_min > timestamp.tm_min)
                    return;
                else if (order_tm.tm_min == timestamp.tm_min)
                {
                    if (order_tm.tm_sec > timestamp.tm_sec)
                        return;
                }
            }

            if (order->getSide() != Order::SELL)
                return;

            if ((maxOrder == nullptr) ||
                order->getPrice() > maxOrder->getPrice())
                maxOrder = order;
        };

        for (const auto& kv: ordersBySymbol)
            max(kv.second);

        return maxOrder;
    }
    catch(std::out_of_range)
    {
        // no order with such symbol
        return nullptr;
    }
}
