#ifndef ORDER_H
#define ORDER_H

#include <time.h>
#include <string>
#include <memory>
#include "CustomTypes.h"

class Order
{
public:
    enum Side
    {
        NONE,
        BUY,
        SELL
    };

    class OrderBuilder
    {
        friend class Order;
    public:
        std::unique_ptr<Order> buildOrder();
        OrderBuilder& setTimestamp(const std::string& tm_str);
        OrderBuilder& setSymbol(const std::string& symbol_str);
        OrderBuilder& setID(const std::string& id_str);
        OrderBuilder& setSide(const std::string& side_str);
        OrderBuilder& setVolume(const std::string& volume_str);
        OrderBuilder& setPrice(const std::string& price_str);
    private:
        CustomTypes::timestamp timestamp = {0};
        std::string symbol;
        unsigned int orderID = 0;
        Side side = NONE;
        unsigned int volume = 0;
        double price = 0.0;
    };


    const CustomTypes::timestamp& getTimestamp() const;
    const std::string& getSymbol() const;
    unsigned int getID() const;
    Side getSide() const;
    unsigned int getVolume() const;
    double getPrice() const;

    void setVolume(unsigned int volume);
    void setPrice(double price);

private:
    Order(const OrderBuilder& orderBuilder);

private:
    CustomTypes::timestamp timestamp = {0};
    std::string symbol;
    unsigned int orderID = 0;
    Side side = NONE;
    unsigned int volume = 0;
    double price = 0.0; // double might not be suitable for the real work (but is ok in scope of this project)
};

inline const CustomTypes::timestamp& Order::getTimestamp() const
{
    return timestamp;
}

inline const std::string& Order::getSymbol() const
{
    return symbol;
}

inline unsigned int Order::getID() const
{
    return orderID;
}

inline Order::Side Order::getSide() const
{
    return side;
}

inline unsigned int Order::getVolume() const
{
    return volume;
}

inline double Order::getPrice() const
{
    return price;
}

inline void Order::setVolume(unsigned int volume)
{
    this->volume = volume;
}

inline void Order::setPrice(double price)
{
    this->price = price;
}

#endif // ORDER_H
