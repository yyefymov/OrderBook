#ifndef TESTSOVERDATA_H
#define TESTSOVERDATA_H

#include "include/OrderBook.h"
#include <string>

class TestsOverData
{
public:
    TestsOverData(const std::string& df)
        : dataFile(df)
    {}

    void testAtTheEndOfData();
    void testAtTimestamp(const std::string& stopAt);
    void testRunRepeatedly(int treshold);

private:
    OrderBook orderBook{};
    std::string dataFile;
};

#endif // TESTSOVERDATA_H
