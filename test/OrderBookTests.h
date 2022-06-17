#ifndef ORDERBOOKTESTS_H
#define ORDERBOOKTESTS_H

#include "gtest/gtest.h"
#include "include/OrderBook.h"

class OrderBookTests : public ::testing::Test
{
public:
    void SetUp() override;
    // void TearDown() override;

//private:
    OrderBook orderBook;
};

#endif // ORDERBOOKTESTS_H
