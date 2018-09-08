#include <gtest/gtest.h>
#include "numbers/number.hpp"

TEST(NumberUtilsTest, SetsValueOfNumberToValueOfGivenNumber) {
    cjr::number<> a = 123;
    cjr::number<> b = 0;

    b.setValue(a);

    EXPECT_EQ(a, b);
}

TEST(NumberUtilsTest, SetsValueOfNumberToGivenValue) {
    cjr::number<> a = 0;

    a.setValue(123);

    EXPECT_EQ(a, cjr::number<>(123));
}

TEST(NumberUtilsTest, ChecksOfNumberValueIsEqualToZero) {
    cjr::number<> a = 0;
    cjr::number<> b = 1;
    cjr::number<> c = -1;

    EXPECT_TRUE(a.isZero());
    EXPECT_FALSE(b.isZero());
    EXPECT_FALSE(c.isZero());
}

TEST(NumberUtilsTest, RevertsNumbersSign) {
    cjr::number<> a = 123;
    cjr::number<> b = -123;

    a.revertSign();
    b.revertSign();

    EXPECT_TRUE(a.isNegative());
    EXPECT_FALSE(b.isNegative());
}