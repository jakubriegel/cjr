#include <gtest/gtest.h>
#include "numbers/number.hpp"


class NumberComparisonTest : public ::testing::Test {
protected:
    cjr::number<> a = 1234;
    cjr::number<> b = 1234;
    cjr::number<> c = 4321;
    cjr::number<> d = -1234;
    cjr::number<> e = -1234;
    cjr::number<> f = -4321;
};

TEST_F(NumberComparisonTest, ChecksNumbersEquality) {
    // by member function
    EXPECT_TRUE(a.isEqual(a));
    EXPECT_TRUE(a.isEqual(b));
    EXPECT_FALSE(a.isEqual(c));
    EXPECT_TRUE(d.isEqual(d));
    EXPECT_TRUE(d.isEqual(e));
    EXPECT_FALSE(d.isEqual(f));
    EXPECT_FALSE(a.isEqual(d));

    // by operator
    EXPECT_TRUE(a == a);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
    EXPECT_TRUE(d == d);
    EXPECT_TRUE(d == e);
    EXPECT_FALSE(d == f);
    EXPECT_FALSE(a == d);

    // by googletest
    EXPECT_EQ(a, a);
    EXPECT_EQ(a, b);
    EXPECT_NE(a, c);
    EXPECT_EQ(d, d);
    EXPECT_EQ(d, e);
    EXPECT_NE(d, f);
    EXPECT_NE(a, d);
}

TEST_F(NumberComparisonTest, ChecksIfNumberIsBiggerThanAnother) {
    // by member function
    EXPECT_TRUE(c.isBigger(a));
    EXPECT_FALSE(a.isBigger(b));
    EXPECT_FALSE(a.isBigger(c));
    EXPECT_TRUE(a.isBigger(d));
    EXPECT_TRUE(d.isBigger(f));
    EXPECT_FALSE(f.isBigger(d));

    // by operator
    EXPECT_TRUE(c > a);
    EXPECT_FALSE(a > b);
    EXPECT_FALSE(a > c);
    EXPECT_TRUE(a > d);
    EXPECT_TRUE(d > f);
    EXPECT_FALSE(f > d);

    // by googletest
    EXPECT_GT(c, a);
    EXPECT_GT(a, d);
    EXPECT_GT(d, f);
}

TEST_F(NumberComparisonTest, ChecksIfNumberIsBiggerOrEqualThanAnother) {
    // by member function
    EXPECT_TRUE(c.isBiggerOrEqual(a));
    EXPECT_TRUE(a.isBiggerOrEqual(a));
    EXPECT_TRUE(a.isBiggerOrEqual(b));
    EXPECT_FALSE(a.isBiggerOrEqual(c));
    EXPECT_TRUE(a.isBiggerOrEqual(d));
    EXPECT_TRUE(d.isBiggerOrEqual(d));
    EXPECT_TRUE(d.isBiggerOrEqual(f));
    EXPECT_FALSE(f.isBiggerOrEqual(d));

    // by operator
    EXPECT_TRUE(c >= a);
    EXPECT_TRUE(a >= a);
    EXPECT_TRUE(a >= b);
    EXPECT_FALSE(a >= c);
    EXPECT_TRUE(a >= d);
    EXPECT_TRUE(d >= d);
    EXPECT_TRUE(d >= f);
    EXPECT_FALSE(f >= d);

    // by googletest
    EXPECT_GE(c, a);
    EXPECT_GE(a, a);
    EXPECT_GE(a, b);
    EXPECT_GE(a, d);
    EXPECT_GE(d, d);
    EXPECT_GE(d, f);
}

TEST_F(NumberComparisonTest, ChecksIfNumberIsSmallerThanAnother) {
    // by member function
    EXPECT_TRUE(a.isSmaller(c));
    EXPECT_FALSE(a.isSmaller(b));
    EXPECT_FALSE(c.isSmaller(a));
    EXPECT_TRUE(d.isSmaller(a));
    EXPECT_TRUE(f.isSmaller(d));
    EXPECT_FALSE(a.isSmaller(f));

    // by operator
    EXPECT_TRUE(a < c);
    EXPECT_FALSE(a < b);
    EXPECT_FALSE(c < a);
    EXPECT_TRUE(d < a);
    EXPECT_TRUE(f < d);
    EXPECT_FALSE(a < f);

    // by googletest
    EXPECT_LT(a, c);
    EXPECT_LT(d, a);
    EXPECT_LT(f, d);
}

TEST_F(NumberComparisonTest, ChecksIfNumberIsSmallerOrEqualThanAnother) {
    // by member function
    EXPECT_TRUE(a.isSmallerOrEqual(c));
    EXPECT_TRUE(a.isSmallerOrEqual(a));
    EXPECT_TRUE(a.isSmallerOrEqual(b));
    EXPECT_FALSE(c.isSmallerOrEqual(a));
    EXPECT_TRUE(d.isSmallerOrEqual(a));
    EXPECT_TRUE(d.isSmallerOrEqual(d));
    EXPECT_TRUE(f.isSmallerOrEqual(d));
    EXPECT_FALSE(a.isSmallerOrEqual(f));

    // by operator
    EXPECT_TRUE(a <= c);
    EXPECT_TRUE(a <= a);
    EXPECT_TRUE(a <= b);
    EXPECT_FALSE(c <= a);
    EXPECT_TRUE(d <= a);
    EXPECT_TRUE(d <= d);
    EXPECT_TRUE(f <= d);
    EXPECT_FALSE(a <= f);

    // by googletest
    EXPECT_LE(a, c);
    EXPECT_LE(a, a);
    EXPECT_LE(a, b);
    EXPECT_LE(d, a);
    EXPECT_LE(d, d);
    EXPECT_LE(f, d);
}

TEST_F(NumberComparisonTest, ThrowsExceptionWhenComparingNumbersWithDifferentBases) {
    cjr::number<> a7(1234, 7);
    cjr::number<> b1231(1234, 1231);

    EXPECT_THROW(a7.isEqual(b1231), cjr::exception::differentBaseException);
    EXPECT_THROW(a7.isBigger(b1231), cjr::exception::differentBaseException);
    EXPECT_THROW(a7.isBiggerOrEqual(b1231), cjr::exception::differentBaseException);
    EXPECT_THROW(a7.isSmaller(b1231), cjr::exception::differentBaseException);
    EXPECT_THROW(a7.isSmallerOrEqual(b1231), cjr::exception::differentBaseException);
}