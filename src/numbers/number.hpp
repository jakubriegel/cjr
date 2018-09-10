#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-explicit-conversions"
#pragma once

#include "cjr.hpp"
#include "exceptions/numberExceptions.hpp"
#include "utils.hpp"

namespace cjr {
    /// \brief a class for storing numbers of any size
    ///
    /// \tparam B defines maximal base of the number, see \ref baseRange
    template <class B = baseRange::medium>
    class number {
    private:
        /// \brief List type for storing digits of \ref number
        using digitList = std::list<B>;
        /// \brief Iterator type for storing iterators for \ref digitList
        using digitIterator = typename std::list<B>::iterator;

        /// \brief Constructs new number with given value and zero as base
        /// \details It was meant to create universal values (see \ref ONE and \ref ZERO) which have the same representation despite of number's base
        /// \warning While implementation of this constructor omits checking base validity it shall not be used in the code
        /// \param initValue the value which the new number will be initialized with, in decimal
        /// \param zeroBase \brief this parameter is making possible for compiler to recognize this constructor
        number(const B & initValue, const bool & zeroBase);

        /// \brief the base of stored number
        const B base;
        /// \brief true when number's value is negative
        bool negative;
        /// \brief digits of stored number
        digitList digits;

        /// \name Calculation Utils
        /// \brief Internal methods for calculation algorithms
        ///@{

        void add(const number<B> & numberToAdd, const B & baseToUse);
        void addAt(digitIterator i, const B & baseToUse, const B & valueToAdd = 1);
        void subtract(const number<B> & numberToSubtract, const B & baseToUse);
        void subtractAt(digitIterator i, const B & baseToUse, const B & valueToSubtract = 1);
        void calculateValueAndProceedOffload(digitIterator & i, const B & newValue,  const B & baseToUse);
        void makeCalculations(
                void (number<B>::* calcFunction)(digitIterator, const B &, const B &),
                const digitList & extraDigits, const B & baseToUse);
        const bool makeComparison(const number<B> & n, bool bigger, const bool & orEqual = false) const;

        ///@}

    public:
        /// \name Universal Values
        /// \brief Values with the same representation with any base.
        /// \details When using them the library is not considering their base. When base is needed for calculations, it is being taken from second \ref number involved in it. Custom universal values can be created with dedicated \ref makeUniversal() "method". Since their base is stored as 0, they should be used only when explicitly needed.
        /// \bug Undefined behaviour when making calculations only on these values.
        ///@{

        /// \brief Universal 1
        static const number<B> ONE;
        /// \brief Universal 0
        static const number<B> ZERO;
        /// \brief Creates universal value with given value
        /// \param initValue value to initialize universal with
        static const number<B> makeUniversal(const B & initValue);

        ///@}

        /// \brief The maximal value of base for each range.
        static const B MAX_BASE;


        /// \brief Constructs new number with 0 value and 10 as base
        number();
        /// \brief Constructs new number with given value and base
        /// \details Beside standard way, you can initialize new number just like a typical variable:
        /// \code cjr::number<> n = 1 \endcode
        /// \detail which will create new number with 1 value and 10 as base
        /// \param initValue the value which the new number will be initialized with, in decimal
        /// \param base base of the new number
        number(const B & initValue, const B & base = 10); // NOLINT(google-explicit-constructor)
        /// \brief Copy constructor for \ref number
        /// \param sourceNumber the number to copy
        number(const number<B> & sourceNumber);

        /// \name Utility
        ///@{

        /// \brief sets new value of the number
        /// \param n the number with source value
        void setValue(const number<B> & n);
        /// \brief sets new value of the number
        /// \param n source value
        void setValue(const B & newValue);
        /// \brief returns true when number's value is 0
        const bool isZero() const;
        /// \brief returns true when number's value is less than 0
        const bool & isNegative() const noexcept { return this->negative; }
        /// \brief reverts the sign of the number
        void revertSign() { this->negative = !this->negative; }
        /// \brief returns absolute value of the number
        const number<B> absoluteValue() const;
        /// \brief returns value of the number converted to String
        /// \param withSeparators when true each digit will be separated with '`'
        const std::string toString(const bool & withSeparators = false) const;
        /// \brief prints to the console value of \ref toString(bool) with new line at the end
        /// \param withSeparators when true each digit will be separated with '`'
        void print(const bool & withSeparators = false) const;

        ///@}

        /// \name Calculation
        /// \note Making calculations on numbers with different bases gives \ref differentBaseException
        /// \note When a std value is added to the \ref number it assumes, that the std value is represented in decimal system. Nevertheless you can add it to the \ref number of any base.
        ///@{

        /// \brief Increments the number
        void increment();
        /// \brief Pre-increments the number
        void operator++();
        /// \brief Post-increments the number
        const number<B> operator++(int);
        /// \brief Adds given number to the number
        void add(const number<B> & numberToAdd);
        /// \brief Adds two given numbers and returns their sum
        number<B> operator+(const number<B> & numberToAdd) const;
        /// \brief Adds given std value to the number
        void add(const B & valueToAdd);
        /// \brief Adds given number and std value and returns their sum as a \ref number
        number<B> operator+(const B & valueToAdd) const;

        /// \brief Decrements the number
        void decrement();
        /// \brief Pre-decrements the number
        void operator--();
        /// \brief Post-decrements the number
        const number<B> operator--(int);
        /// \brief Subtracts given number from the number
        void subtract(const number<B> & numberToSubtract);
        /// \brief Subtracts two given numbers and returns their difference
        number<B> operator-(const number<B> & numberToSubtract) const;
        /// \brief Subtracts given std value from the number
        void subtract(const B & valueToSubtract);
        /// \brief Subtracts std value from given number and returns their difference as a \ref number
        number<B> operator-(const B & valueToSubtract) const;

        ///@}

        /// \name Comparison
        /// \note Comparing numbers with different bases gives \ref differentBaseException
        ///@{

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

        ///@}

        /// \brief Returns true when both numbers have the same base
        /// \detail When comparing to universal value(see \ref ZERO, \ref ONE) also return true
        /// \param a First \ref number to check
        /// \param b Second \ref number to check
        /// \return
        static const bool haveSameBases(const number<B> & a, const number<B> & b) { return a.getBase() == b.getBase() || a.getBase() == 0 || b.getBase() == 0; }
        /// \brief Throws \ref differentBaseException when bases of given \ref number "numbers" are different
        /// \param a First \ref number to check
        /// \param b Second \ref number to check
        static void assertHaveSameBases(const number<B> & a, const number<B> & b) { if(!number::haveSameBases(a, b)) throw exception::differentBaseException(); }
        /// \brief Throws \ref invalidBaseException when given base doesn't meet base requirements
        /// \param givenBase Base to test
        static const B & assertBaseIsValid(const B & givenBase);

        /// \name Getters
        ///@{

        const B & getBase() const noexcept { return this->base; }
        const digitList & getDigits() const noexcept { return this->digits; }

        ///@}
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

#pragma clang diagnostic pop