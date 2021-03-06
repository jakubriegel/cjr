#include <gtest/gtest.h>
#include "numbers/number.hpp"


class NumberMultiplyDivideTest : public ::testing::Test {
protected:
    cjr::number<> a = 5;
    cjr::number<> b = 13;
    cjr::number<> c = -10;
    cjr::number<> d = -2;
    cjr::number<> e = 2;
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
    a.multiplyByBase();
    EXPECT_EQ(a, cjr::number<>(50));

    c.multiplyByBase(5);
    EXPECT_EQ(c, cjr::number<>(-1000000));
}

TEST_F(NumberMultiplyDivideTest, ThrowsExceptionWhenDividingByZero) {
    EXPECT_THROW(a.divide(0), cjr::exception::divisionByZeroException);
}

TEST_F(NumberMultiplyDivideTest, DividesNumberByNumber) {
    // positive and positive
    a.divide(2);
    EXPECT_EQ(a, cjr::number<>(2));

    // positive and negative
    b.divide(d);
    EXPECT_EQ(b, cjr::number<>(-6));

    // negative and negative
    c.divide(d);
    EXPECT_EQ(c, cjr::number<>(5));
}

TEST_F(NumberMultiplyDivideTest, DividesNumberByStdValue) {
    // positive and positive
    a.divide(50);
    EXPECT_EQ(a, cjr::number<>(0));

    // positive and negative
    b.divide(-13);
    EXPECT_EQ(b, cjr::number<>(-1));

    // negative and negative
    c.divide(-2);
    EXPECT_EQ(c, cjr::number<>(5));
}

TEST_F(NumberMultiplyDivideTest, DividesNumberByBase) {
    a.divideByBase();
    EXPECT_EQ(a, cjr::number<>(0));

    c.divideByBase();
    EXPECT_EQ(c, cjr::number<>(-1));
}

TEST_F(NumberMultiplyDivideTest, ReturnsDivisionRemainder) {
    EXPECT_EQ(a.remainder(2), cjr::number<>(1));
    
    EXPECT_EQ(c.remainder(10), cjr::number<>(0));
}