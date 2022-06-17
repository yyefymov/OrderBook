#include "OrderBookTests.h"

TEST_F(OrderBookTests, TestBestSellAtTime)
{
    auto expectedOrder = orderBook.getOrder(2837177);

    ASSERT_TRUE(expectedOrder);

    CustomTypes::timestamp time;
    time.tm_hour = 9;
    time.tm_min = 2;
    time.tm_sec = 20;

    auto bestSell = orderBook.bestSellAtTime("DVAM1", time);

    ASSERT_TRUE(bestSell);

    EXPECT_EQ(bestSell->getID(), expectedOrder->getID());
}

TEST_F(OrderBookTests, TestBiggestBuyOrders)
{
    auto biggestBuyOrders = orderBook.biggestBuyOrders("DVAM1");

    ASSERT_EQ(biggestBuyOrders.size(), 3);

    EXPECT_EQ(biggestBuyOrders[0]->getID(), 2837186);
    EXPECT_EQ(biggestBuyOrders[1]->getID(), 2837183);
    EXPECT_EQ(biggestBuyOrders[2]->getID(), 2837184);
}

TEST_F(OrderBookTests, TestBiggestBuyOrdersNotEnoughOrders)
{
    orderBook.cancel(2837186);
    orderBook.cancel(2837185);
    orderBook.cancel(2837184);
    orderBook.cancel(2837182);

    auto biggestBuyOrders = orderBook.biggestBuyOrders("DVAM1");

    EXPECT_EQ(biggestBuyOrders.size(), 1);
}

TEST_F(OrderBookTests, TestOrderCounts)
{
    auto orderCounts = orderBook.orderCounts();

    EXPECT_EQ(orderCounts["DVAM1"], 9);
    EXPECT_EQ(orderCounts["DVAM2"], 3);
}

TEST_F(OrderBookTests, TestGetOrder)
{
    auto order = orderBook.getOrder(2837175);

    tm exp_timestamp;
    exp_timestamp.tm_hour = 9;
    exp_timestamp.tm_min = 0;
    exp_timestamp.tm_sec = 0;

    ASSERT_TRUE(order);

    EXPECT_EQ(order->getTimestamp().tm_hour, exp_timestamp.tm_hour);
    EXPECT_EQ(order->getTimestamp().tm_min, exp_timestamp.tm_min);
    EXPECT_EQ(order->getTimestamp().tm_sec, exp_timestamp.tm_sec);
    EXPECT_EQ(order->getSymbol(), "DVAM1");
    EXPECT_EQ(order->getID(), 2837175);
    EXPECT_EQ(order->getSide(), Order::SELL);
    EXPECT_EQ(order->getVolume(), 72);
    EXPECT_EQ(order->getPrice(), 36.30);
}

TEST_F(OrderBookTests, TestCancelOrder)
{
    const unsigned int order_id = 2837175;
    orderBook.cancel(order_id);
    EXPECT_TRUE(orderBook.getOrder(order_id) == nullptr);
}

TEST_F(OrderBookTests, TestAmendOrder)
{
    const unsigned int order_id = 2837175;
    const int newVolume = 80;
    const double newPrice = 40.90;

    orderBook.amend(order_id, newVolume, newPrice);

    auto order = orderBook.getOrder(order_id);

    EXPECT_EQ(order->getVolume(), newVolume);
    EXPECT_EQ(order->getPrice(), newPrice);
}

TEST_F(OrderBookTests, TestInsertExistingOrder)
{
    const unsigned int order_id = 2837175;
    const unsigned int currentVolume = orderBook.getOrder(order_id)->getVolume();
    const double currentPrice = orderBook.getOrder(order_id)->getPrice();

    auto updatedOrder = std::make_shared<Order>(*orderBook.getOrder(order_id));
    updatedOrder->setPrice(999.0);
    updatedOrder->setVolume(117);

    orderBook.insert(updatedOrder);

    EXPECT_EQ(orderBook.getOrder(order_id)->getVolume(), currentVolume);
    EXPECT_EQ(orderBook.getOrder(order_id)->getPrice(), currentPrice);
}


void OrderBookTests::SetUp()
{
    auto orderBuilder = Order::OrderBuilder{};

    orderBook.insert(
                orderBuilder.setTimestamp("09:00:00.690000").
                setSymbol("DVAM1").setID("2837175").setSide("SELL")
                .setVolume("72").setPrice("36.30").buildOrder());

    orderBook.insert(
                orderBuilder.setTimestamp("09:00:00.700000").
                setSymbol("DVAM1").setID("2837176").setSide("SELL")
                .setVolume("6").setPrice("36.30").buildOrder());

    orderBook.insert(
                orderBuilder.setTimestamp("09:01:00.700000").
                setSymbol("DVAM1").setID("2837177").setSide("SELL")
                .setVolume("90").setPrice("100.33").buildOrder());

    orderBook.insert(
                orderBuilder.setTimestamp("09:01:20.700000").
                setSymbol("DVAM1").setID("2837178").setSide("SELL")
                .setVolume("90").setPrice("100.30").buildOrder());

    orderBook.insert(
                orderBuilder.setTimestamp("09:01:40.700000").
                setSymbol("DVAM2").setID("2837179").setSide("SELL")
                .setVolume("100").setPrice("100.34").buildOrder());

    orderBook.insert(
                orderBuilder.setTimestamp("09:02:00.700000").
                setSymbol("DVAM2").setID("2837180").setSide("SELL")
                .setVolume("36").setPrice("9.30").buildOrder());

    orderBook.insert(
                orderBuilder.setTimestamp("09:02:20.700000").
                setSymbol("DVAM2").setID("2837181").setSide("BUY")
                .setVolume("59").setPrice("35.30").buildOrder());

    orderBook.insert(
                orderBuilder.setTimestamp("09:02:40.700000").
                setSymbol("DVAM1").setID("2837182").setSide("BUY")
                .setVolume("9").setPrice("9.60").buildOrder());

    orderBook.insert(
                orderBuilder.setTimestamp("09:03:00.700000").
                setSymbol("DVAM1").setID("2837183").setSide("BUY")
                .setVolume("70").setPrice("11.30").buildOrder());

    orderBook.insert(
                orderBuilder.setTimestamp("09:03:20.700000").
                setSymbol("DVAM1").setID("2837184").setSide("BUY")
                .setVolume("41").setPrice("9.35").buildOrder());

    orderBook.insert(
                orderBuilder.setTimestamp("09:03:30.700000").
                setSymbol("DVAM1").setID("2837185").setSide("BUY")
                .setVolume("14").setPrice("40.60").buildOrder());

    orderBook.insert(
                orderBuilder.setTimestamp("09:03:40.700000").
                setSymbol("DVAM1").setID("2837186").setSide("BUY")
                .setVolume("84").setPrice("9.67").buildOrder());
}
