#include <iostream>
#include <fstream>
#include <sstream>
#include "include/OrderBook.h"
#include <gtest/gtest.h>
#include "test/OrderTests.h"
#include "test/OrderBookTests.h"
#include "test/testsOverData/TestsOverData.h"

using namespace std;


int main()
{
    TestsOverData tod("P:/QtProjects/OrderBook/orders.dat");

    tod.testAtTheEndOfData();
    tod.testAtTimestamp("15:30:00");
    tod.testRunRepeatedly(5000);

    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
