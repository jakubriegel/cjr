#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-explicit-conversions"
#ifndef CJR_NUMBER_HPP
#define CJR_NUMBER_HPP

#include "cjr.hpp"
#include "exceptions/numberExceptions.hpp"
#include "utils.hpp"

namespace cjr {

    template <class B = baseRange::medium>
    class number {
    private:
        using digitList = std::list<B>;
        using digitIterator = typename std::list<B>::iterator;

        explicit number(const B & initValue, const bool & zeroBase);

        const B base;

        bool negative;
        digitList digits;

        void addAt(digitIterator i, const B & baseToUse, const B & valueToAdd = 1);
        void subtractAt(digitIterator i, const B & baseToUse, const B & valueToSubtract = 1);
        void calculateValueAndProceedOffload(digitIterator & i, const B & newValue,  const B & baseToUse);
        void makeCalculations(
                void (number<B>::* calcFunction)(digitIterator, const B &, const B &),
                const digitList & extraDigits, const B & baseToUse);
        const bool makeComparison(const number<B> & n, bool bigger, const bool & orEqual = false) const;

    public:
        static const number<B> ONE;
        static const B MAX_BASE;

        // constructors
        number();
        number(const B & initValue, const B & base = 10); // NOLINT(google-explicit-constructor)
        number(const number<B> & sourceNumber);

        // utils
        void setValue(const number<B> & a);
        void setValue(const B & newValue);
        const bool isZero() const;
        const bool & isNegative() const noexcept { return this->negative; }
        void revertSign() { this->negative = !this->negative; }
        const number<B> absoluteValue() const;
        static const number<B> makeOne();
        const std::string toString(const bool & withSeparators = false) const;
        void print(const bool & withSeparators = false) const;

        // calculations
        void increment();
        void add(const number<B> & numberToAdd);
        void add(const number<B> & numberToAdd, const B & baseToUse);
        void add(const B & valueToAdd);

        void decrement();
        void subtract(const number<B> & numberToSubtract);
        void subtract(const number<B> & numberToSubtract, const B & baseToUse);
        void subtract(const B & valueToSubtract);

        // comparisons
        const bool isBigger(const number<B> & a, const bool & orEqual = false) const;
        const bool operator>(const number<B> & a) const;
        const bool isBiggerOrEqual(const number<B> & a) const;
        const bool operator>=(const number<B> & a) const;
        const bool isSmaller(const number<B> & a, const bool & orEqual = false) const;
        const bool operator<(const number<B> & a) const;
        const bool isSmallerOrEqual(const number<B> & a) const;
        const bool operator<=(const number<B> & a) const;
        const bool isEqual(const number<B> & n) const;
        const bool operator==(const number<B> & a) const;
        const bool operator!=(const number<B> & a) const;

        static const bool haveSameBases(const number<B> & a, const number<B> & b) { return a.getBase() == b.getBase() || a.getBase() == 0 || b.getBase() == 0; }
        static void assertHaveSameBases(const number<B> & a, const number<B> & b) { if(!number::haveSameBases(a, b)) throw exception::differentBaseException(); }
        static const B & assertBaseIsValid(const B & givenBase);

        // getters
        const B & getBase() const noexcept { return this->base; }
        const digitList & getDigits() const noexcept { return this->digits; }
    };

//    template class number<baseRange::binary>;
    template class number<baseRange::small>;
    template class number<baseRange::medium>;
    template class number<baseRange::big>;
    template class number<baseRange::huge>;

    template <class B>
    std::ostream & operator<<(std::ostream & os, const number<B> & n) {
        os << n.toString();
        return os;
    }
}

#endif //CJR_NUMBER_HPP

#pragma clang diagnostic pop