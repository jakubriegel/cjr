#include <gtest/gtest.h>
#include "numbers/number.hpp"


class NumberMultiplyDivideTest : public ::testing::Test {
protected:
    cjr::number<> a = 5;
    cjr::number<> b = 13;
    cjr::number<> c = -10;
    cjr::number<> d = -2;
};

TEST_F(NumberMultiplyDivideTest, MultpliesNumberByNumber) {
    // positive and positive
    a.multiply(b);
    EXPECT_EQ(a, cjr::number<>(65));

    // positive and negative
    b.multiply(c);
    EXPECT_EQ(b, cjr::number<>(-130));

    // negative and negative
    c.multiply(d);
    EXPECT_EQ(c, cjr::number<>(20));
}

TEST_F(NumberMultiplyDivideTest, MultipliesNumberByStdValue) {
    // positive and positive
    a.multiply(13);
    EXPECT_EQ(a, cjr::number<>(65));

    // positive and negative
    b.multiply(-10);
    EXPECT_EQ(b, cjr::number<>(-130));

    // negative and negative
    c.multiply(-2);
    EXPECT_EQ(c, cjr::number<>(20));
}

TEST_F(NumberMultiplyDivideTest, RaisesNumberToThePower) {
    a.power();
    EXPECT_EQ(a, cjr::number<>(25));

    c.power(5);
    EXPECT_EQ(c, cjr::number<>(-100000));
}

TEST_F(NumberMultiplyDivideTest, MultipliesNumberByBase) {
    a.timesBase();
    EXPECT_EQ(a, cjr::number<>(50));

    c.timesBase(5);
    EXPECT_EQ(c, cjr::number<>(-1000000));
}
