#ifndef ORDERTESTS_H
#define ORDERTESTS_H

#include <gtest/gtest.h>

class OrderTests : public ::testing::Test
{
public:
    void SetUp() override;

    std::shared_ptr<class Order> order;
};

#endif // ORDERTESTS_H
