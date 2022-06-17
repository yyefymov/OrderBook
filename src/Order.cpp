#include "include/Order.h"
#include <sstream>
#include <iostream>

Order::Order(const OrderBuilder& orderBuilder)
{
    timestamp = orderBuilder.timestamp;
    symbol = orderBuilder.symbol;
    orderID = orderBuilder.orderID;
    side = orderBuilder.side;
    volume = orderBuilder.volume;
    price = orderBuilder.price;
}

std::unique_ptr<Order> Order::OrderBuilder::buildOrder()
{
    return std::unique_ptr<Order>(new Order(*this));
}

Order::OrderBuilder& Order::OrderBuilder::setTimestamp(const std::string &tm_str)
{
    // HH:MM:SS.000000

    std::istringstream tm_stream(tm_str);
    std::string buf;
    if (std::getline(tm_stream, buf, ':'))
    {
        timestamp.tm_hour = std::stoi(buf);
    }
    if (std::getline(tm_stream, buf, ':'))
    {
        timestamp.tm_min = std::stoi(buf);
    }
    if (std::getline(tm_stream, buf, ':'))
    {
        std::istringstream sec_stream(buf);
        std::string sec_buf;
        if (std::getline(sec_stream, sec_buf, '.'))
        {
            timestamp.tm_sec = std::stoi(sec_buf);
        }
        if (std::getline(sec_stream, sec_buf, '.'))
        {
            timestamp.tm_usec = std::stoi(sec_buf);
        }
    }
    return *this;
}

Order::OrderBuilder& Order::OrderBuilder::setSymbol(const std::string &symbol_str)
{
    symbol = symbol_str;
    return *this;
}

Order::OrderBuilder& Order::OrderBuilder::setID(const std::string &id_str)
{
    orderID = std::stoul(id_str);
    return *this;
}

Order::OrderBuilder& Order::OrderBuilder::setSide(const std::string &side_str)
{
    if (side_str == "SELL")
        side = Order::SELL;
    else if (side_str == "BUY")
        side = Order::BUY;
    else
    {
        // error!
        side = Order::NONE;
    }
    return *this;
}

Order::OrderBuilder& Order::OrderBuilder::setVolume(const std::string &volume_str)
{
    volume = std::stoul(volume_str);
    return *this;
}

Order::OrderBuilder& Order::OrderBuilder::setPrice(const std::string &price_str)
{
    price = std::stod(price_str);
    return *this;
}
