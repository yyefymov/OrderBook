#include "TestsOverData.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void TestsOverData::testAtTheEndOfData()
{
    std::ifstream inputFile(dataFile);
    string line;
    while (std::getline(inputFile, line))
    {
        Order::OrderBuilder orderBuilder;
        std::istringstream inputLine(line);

        string timestamp;
        string symbol;
        string orderID;
        string operation;
        string side;
        string volume;
        string price;

        std::getline(inputLine, timestamp, ';');
        std::getline(inputLine, symbol, ';');
        std::getline(inputLine, orderID, ';');
        std::getline(inputLine, operation, ';');
        std::getline(inputLine, side, ';');
        std::getline(inputLine, volume, ';');
        std::getline(inputLine, price, ';');

        if (operation == "I")
            orderBook.insert(
                        orderBuilder.setTimestamp(timestamp).setSymbol(symbol)
                        .setID(orderID).setSide(side).setVolume(volume).setPrice(price)
                        .buildOrder());
        else if (operation == "C")
            orderBook.cancel(std::stoul(orderID));
        else if (operation == "A")
             orderBook.amend(std::stoul(orderID), std::stoul(volume), std::stod(price));
        else
        {
            // unknown operation
        }
    }


    // test
    auto count = orderBook.orderCounts();
    cout << "Order count by symbol:" << endl;
    for (const auto& kv: count)
        cout << kv.first << ": " << kv.second << endl;
    cout << endl << endl;

    auto topBuyOrders = orderBook.biggestBuyOrders("DVAM1");
    cout << "Biggest buy DVAM1 orders:" << endl;
    for (const auto& order: topBuyOrders)
        cout << "Order ID: " << order->getID() << "; volume: " << order->getVolume() << endl;
    cout << endl << endl;

    CustomTypes::timestamp timestamp;
    timestamp.tm_hour = 15;
    timestamp.tm_min = 30;
    timestamp.tm_sec = 00;
    auto topSellOrder = orderBook.bestSellAtTime("DVAM2", timestamp);
    if (topSellOrder)
    {
        cout << "Biggest sell at " << timestamp.to_string() << endl;
        cout << "Order ID: " << topSellOrder->getID() << "; volume: " << topSellOrder->getVolume() << "; price: " << topSellOrder->getPrice() << endl;
    }
    else
    {
        cout << "No SELL order at " << timestamp.to_string() << endl;
    }
    cout << endl << endl;

    orderBook = OrderBook();
}

void TestsOverData::testAtTimestamp(const string &stopAt)
{

    CustomTypes::timestamp tm_stopAt;
    {
        istringstream inputTimestamp(stopAt);
        string tm_buf;

        getline(inputTimestamp, tm_buf, ':');
        tm_stopAt.tm_hour = std::stoi(tm_buf);

        getline(inputTimestamp, tm_buf, ':');
        tm_stopAt.tm_min = std::stoi(tm_buf);

        getline(inputTimestamp, tm_buf, ':');
        tm_stopAt.tm_sec = std::stoi(tm_buf);
    }

    std::ifstream inputFile(dataFile);
    string line;
    while (std::getline(inputFile, line))
    {
        Order::OrderBuilder orderBuilder;
        std::istringstream inputLine(line);

        string timestamp;
        string symbol;
        string orderID;
        string operation;
        string side;
        string volume;
        string price;

        getline(inputLine, timestamp, ';');
        getline(inputLine, symbol, ';');
        getline(inputLine, orderID, ';');
        getline(inputLine, operation, ';');
        getline(inputLine, side, ';');
        getline(inputLine, volume, ';');
        getline(inputLine, price, ';');


        CustomTypes::timestamp tm_order;
        {
            istringstream inputTimestamp(timestamp);
            string tm_buf;

            getline(inputTimestamp, tm_buf, ':');
            tm_order.tm_hour = std::stoi(tm_buf);

            getline(inputTimestamp, tm_buf, ':');
            tm_order.tm_min = std::stoi(tm_buf);

            getline(inputTimestamp, tm_buf, ':');
            tm_order.tm_sec = std::stoi(tm_buf);
        }

        if (tm_order.tm_hour >= tm_stopAt.tm_hour &&
            tm_order.tm_min >= tm_stopAt.tm_min &&
            tm_order.tm_sec >= tm_stopAt.tm_sec)
            break;


        if (operation == "I")
            orderBook.insert(
                        orderBuilder.setTimestamp(timestamp).setSymbol(symbol)
                        .setID(orderID).setSide(side).setVolume(volume).setPrice(price)
                        .buildOrder());
        else if (operation == "C")
            orderBook.cancel(std::stoul(orderID));
        else if (operation == "A")
             orderBook.amend(std::stoul(orderID), std::stoul(volume), std::stod(price));
        else
        {
            // unknown operation
        }
    }

    // test
    auto count = orderBook.orderCounts();
    cout << "Order count by symbol:" << endl;
    for (const auto& kv: count)
        cout << kv.first << ": " << kv.second << endl;
    cout << endl << endl;

    auto topBuyOrders = orderBook.biggestBuyOrders("DVAM1");
    cout << "Biggest buy DVAM1 orders:" << endl;
    for (const auto& order: topBuyOrders)
        cout << "Order ID: " << order->getID() << "; volume: " << order->getVolume() << endl;
    cout << endl << endl;

    CustomTypes::timestamp timestamp;
    timestamp.tm_hour = 15;
    timestamp.tm_min = 30;
    timestamp.tm_sec = 00;
    auto topSellOrder = orderBook.bestSellAtTime("DVAM1", timestamp);
    if (topSellOrder)
    {
        cout << "Biggest sell at " << timestamp.to_string() << endl;
        cout << "Order ID: " << topSellOrder->getID() << "; volume: " << topSellOrder->getVolume() << "; price: " << topSellOrder->getPrice() << endl;
    }
    else
    {
        cout << "No SELL order at " << timestamp.to_string() << endl;
    }
    cout << endl << endl;


    orderBook = OrderBook();
}

void TestsOverData::testRunRepeatedly(int treshold)
{
    int counter = 0;
    std::ifstream inputFile(dataFile);
    string line;
    while (std::getline(inputFile, line))
    {
        Order::OrderBuilder orderBuilder;
        std::istringstream inputLine(line);

        string timestamp;
        string symbol;
        string orderID;
        string operation;
        string side;
        string volume;
        string price;

        getline(inputLine, timestamp, ';');
        getline(inputLine, symbol, ';');
        getline(inputLine, orderID, ';');
        getline(inputLine, operation, ';');
        getline(inputLine, side, ';');
        getline(inputLine, volume, ';');
        getline(inputLine, price, ';');

        if (operation == "I")
            orderBook.insert(
                        orderBuilder.setTimestamp(timestamp).setSymbol(symbol)
                        .setID(orderID).setSide(side).setVolume(volume).setPrice(price)
                        .buildOrder());
        else if (operation == "C")
            orderBook.cancel(std::stoul(orderID));
        else if (operation == "A")
             orderBook.amend(std::stoul(orderID), std::stoul(volume), std::stod(price));
        else
        {
            // unknown operation
        }
        ++counter;

        // run tests every 'treshold' entry
        if (counter == treshold)
        {
            counter = 0;

            CustomTypes::timestamp tm_order;
            {
                istringstream inputTimestamp(timestamp);
                string tm_buf;

                getline(inputTimestamp, tm_buf, ':');
                tm_order.tm_hour = std::stoi(tm_buf);

                getline(inputTimestamp, tm_buf, ':');
                tm_order.tm_min = std::stoi(tm_buf);

                getline(inputTimestamp, tm_buf, '.');
                tm_order.tm_sec = std::stoi(tm_buf);

                getline(inputTimestamp, tm_buf, '.');
                tm_order.tm_usec = std::stoi(tm_buf);
            }
            cout << "Collect order book info at " << tm_order.to_string() << endl << endl;

            auto count = orderBook.orderCounts();
            cout << "Order count by symbol:" << endl;
            for (const auto& kv: count)
                cout << kv.first << ": " << kv.second << endl;
            cout << endl << endl;

            auto topBuyOrders = orderBook.biggestBuyOrders("DVAM1");
            cout << "Biggest buy DVAM1 orders:" << endl;
            for (const auto& order: topBuyOrders)
                cout << "Order ID: " << order->getID() << "; volume: " << order->getVolume() << endl;
            cout << endl << endl;


            auto topSellOrder = orderBook.bestSellAtTime("DVAM1", tm_order);
            if (topSellOrder)
            {
                cout << "Biggest sell at " << tm_order.to_string() << endl;
                cout << "Order ID: " << topSellOrder->getID() << "; volume: " << topSellOrder->getVolume() << "; price: " << topSellOrder->getPrice() << endl;
            }
            else
            {
                cout << "No SELL order at " << tm_order.to_string() << endl;
            }
            cout << endl << endl;
        }

    }

    orderBook = OrderBook();
}
