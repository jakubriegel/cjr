#include <gtest/gtest.h>
#include "numbers/number.hpp"

class NumberAddSubtractTest : public ::testing::Test {
protected:
    cjr::number<> a = 10;
    cjr::number<> b = 23;
    cjr::number<> c = -10;
    cjr::number<> d = -23;
    cjr::number<> e = 100;
    cjr::number<> f = 10;
    cjr::number<> g = -15;
};

TEST_F(NumberAddSubtractTest, IncrementsNumber) {
    // with method
    a.increment();
    ASSERT_EQ(a, cjr::number<>(11));

    for(unsigned int i = 0; i < 100; i++) {
        b.increment();
        c.increment();
    }
    EXPECT_EQ(b, cjr::number<>(123));
    EXPECT_EQ(c, cjr::number<>(90));

    // with operator
    f++;
    ASSERT_EQ(f, cjr::number<>(11));

    for(unsigned int i = 0; i < 100; i++) {
        e++;
        g++;
    }
    EXPECT_EQ(e, cjr::number<>(200));
    EXPECT_EQ(g, cjr::number<>(85));
}

TEST_F(NumberAddSubtractTest, DecrementsNumber) {
    // with method
    a.decrement();
    ASSERT_EQ(a, cjr::number<>(9));

    for(unsigned int i = 0; i < 100; i++) {
        d.decrement();
        f.decrement();
    }
    EXPECT_EQ(d, cjr::number<>(-123));
    EXPECT_EQ(f, cjr::number<>(-90));

    // with operator
    b--;
    ASSERT_EQ(b, cjr::number<>(22));

    for(unsigned int i = 0; i < 100; i++) {
        e--;
        g--;
    }
    EXPECT_EQ(e, cjr::number<>(0));
    EXPECT_EQ(g, cjr::number<>(-115));
}

TEST_F(NumberAddSubtractTest, AddsNumbers) {
    // positive to positive
    a.add(b);
    EXPECT_EQ(a, cjr::number<>(33));

    // positive to negative, not exceeding zero
    g.add(cjr::number<>(5));
    EXPECT_EQ(g, c);

    // positive to negative, exceeding zero
    c.add(cjr::number<>(33));
    EXPECT_EQ(c, b);

    // negative to positive, not exceeding zero
    b.add(cjr::number<>(-13));
    EXPECT_EQ(b, f);

    // negative to positive, exceeding zero
    e.add(cjr::number<>(-123));
    EXPECT_EQ(e, d);
}

TEST_F(NumberAddSubtractTest, SubtractsNumbers) {
    // minuend >= 0, subtrahend > 0
    // subtrahend > minuend
    b.subtract(e);
    EXPECT_EQ(b, cjr::number<>(-77));
    // subtrahend < minuend
    f.subtract(c);
    EXPECT_EQ(f, cjr::number<>(20));

    // minuend < 0, subtrahend > 0
    c.subtract(e);
    EXPECT_EQ(c, cjr::number<>(-110));

    // any minuend, subtrahend < 0
    a.subtract(g);
    EXPECT_EQ(a, cjr::number<>(25));
    d.subtract(g);
    EXPECT_EQ(d, cjr::number<>(-8));
}

TEST_F(NumberAddSubtractTest, AddsBaseDataTypeToNumber) {
    // positive to positive
    a.add(13);
    EXPECT_EQ(a, b);

    // positive to negative, not exceeding zero
    g.add(5);
    EXPECT_EQ(g, c);

    // positive to negative, exceeding zero
    c.add(33);
    EXPECT_EQ(c, b);

    // negative to positive, not exceeding zero
    b.add(-13);
    EXPECT_EQ(b, f);

    // negative to positive, exceeding zero
    e.add(-123);
    EXPECT_EQ(e, d);
}

TEST_F(NumberAddSubtractTest, SubtractsBaseDataTypeFromNumber) {
    // minuend >= 0, subtrahend > 0
    // subtrahend > minuend
    b.subtract(100);
    EXPECT_EQ(b, cjr::number<>(-77));
    // subtrahend < minuend
    f.subtract(-10);
    EXPECT_EQ(f, cjr::number<>(20));

    // minuend < 0, subtrahend > 0
    c.subtract(100);
    EXPECT_EQ(c, cjr::number<>(-110));

    // any minuend, subtrahend < 0
    a.subtract(-15);
    EXPECT_EQ(a, cjr::number<>(25));
    d.subtract(-15);
    EXPECT_EQ(d, cjr::number<>(-8));
}
