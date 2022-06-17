#include "OrderTests.h"
#include "include/Order.h"

void OrderTests::SetUp()
{
    auto orderBuilder = Order::OrderBuilder{};
    order =
        orderBuilder.setTimestamp("09:00:00.690000").
        setSymbol("DVAM1").setID("2837175").setSide("SELL")
        .setVolume("72").setPrice("36.30").buildOrder();
}


TEST_F(OrderTests, TestBuildOrder)
{
    ASSERT_TRUE(order);

    EXPECT_EQ(order->getTimestamp().tm_hour, 9);
    EXPECT_EQ(order->getTimestamp().tm_min, 0);
    EXPECT_EQ(order->getTimestamp().tm_sec, 0);
    EXPECT_EQ(order->getTimestamp().tm_usec, 690000);

    EXPECT_EQ(order->getSymbol(), "DVAM1");
    EXPECT_EQ(order->getID(), 2837175);
    EXPECT_EQ(order->getSide(), Order::SELL);
    EXPECT_EQ(order->getVolume(), 72);
    EXPECT_EQ(order->getPrice(), 36.30);
}

TEST_F(OrderTests, TestModifyVolume)
{
    order->setVolume(92);

    EXPECT_EQ(order->getVolume(), 92);
}

TEST_F(OrderTests, TestModifyPrice)
{
    order->setPrice(60.0);

    EXPECT_EQ(order->getPrice(), 60.0);
}
