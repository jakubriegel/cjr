#include <gtest/gtest.h>
#include "numbers/number.hpp"

TEST(NumberGeneralTest, ChecksIfTwoNumbersHaveSameBases) {
    cjr::number<> a(1, 2);
    cjr::number<> b(12, 2);
    cjr::number<> c(1, 11);

    EXPECT_TRUE(cjr::number<>::haveSameBases(a, b)) << "should return true when numbers have equal bases";
    EXPECT_FALSE(cjr::number<>::haveSameBases(a, c)) << "should return false when numbers have different bases";
}

TEST(NumberGeneralTest, CreatesNumberWith0ValueAnd10AsBase) {
    cjr::number<> n;

    EXPECT_EQ(n, cjr::number<>(0));
    EXPECT_EQ(n.getBase(), 10);
}

TEST(NumberGeneralTest, CreatesNumbersWithGivenValueAnd10AsBase) {
    cjr::number<> a = 0;
    cjr::number<> b = 11;
    cjr::number<> c = 123123;

    EXPECT_EQ(a, 0);
    EXPECT_EQ(b, 11);
    EXPECT_EQ(c, 123123);
}

TEST(NumberGeneralTest, CopiesValueOfPArameterNumberToNewOne) {
    cjr::number<> a = 123;
    cjr::number<> b(a);

    EXPECT_EQ(a, b);
}

TEST(NumberGeneralTest, ThrowsExceptionWhenCreatingNumberWithBaseExceedingTheLimit) {
    const auto smallBase = static_cast<const cjr::baseRange::small>(
            cjr::number<cjr::baseRange::small>::MAX_BASE + 1);
    const auto mediumBase = static_cast<const cjr::baseRange::medium>(
            cjr::number<cjr::baseRange::medium>::MAX_BASE + 1);
    const auto bigBase = static_cast<const cjr::baseRange::big>(
            cjr::number<cjr::baseRange::big>::MAX_BASE + 1);
    const auto hugeBase = static_cast<const cjr::baseRange::huge>(
            cjr::number<cjr::baseRange::huge>::MAX_BASE + 1);

    EXPECT_THROW(cjr::number<cjr::baseRange::small> a(100, smallBase), cjr::exception::invalidBaseException);
    EXPECT_THROW(cjr::number<cjr::baseRange::medium> b(100, mediumBase), cjr::exception::invalidBaseException);
    EXPECT_THROW(cjr::number<cjr::baseRange::big> c(100, bigBase), cjr::exception::invalidBaseException);
    EXPECT_THROW(cjr::number<cjr::baseRange::huge> d(100, hugeBase), cjr::exception::invalidBaseException);
}

TEST(NumberGeneralTest, ThrowsExceptionWhenNumbersHaveDifferentBases) {
    cjr::number<> a(1234, 7);
    cjr::number<> b(1234, 1231);

    EXPECT_THROW(cjr::number<>::assertHaveSameBases(a, b), cjr::exception::differentBaseException);
}

TEST(NumberGeneralTest, IsAbleToStoreNumbersExceedingTheRangeOfTypicalVariable)
{
    cjr::number<> a = 4000000000;
    cjr::number<> b = 4000000000;

    EXPECT_NO_THROW(a.add(b));
}

TEST(NumberGeneralTest, ConvertsNumberValueToString) {
    cjr::number<> a = 123123;

    EXPECT_STREQ(a.toString().c_str(), "123123");
}

