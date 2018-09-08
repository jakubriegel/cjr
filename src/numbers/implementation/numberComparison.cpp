
#include <numbers/number.hpp>

#include "numbers/number.hpp"

namespace cjr {
    template<class B>
    const bool number<B>::makeComparison(const number<B> & n, bool bigger, const bool & orEqual) const {
        number<B>::assertHaveSameBases(*this, n);

        // if numbers have different signs, return without calculation
        if(this->isNegative() != n.isNegative()) {
            if(bigger) return !this->isNegative() && n.isNegative();
            return this->isNegative() && !n.isNegative();
        }

        // if both numbers are negative revert bigger flag
        if(this->isNegative() && n.isNegative()) bigger = !bigger;

        // make comparison

        static auto compare = [](const B & a, const B & b, const bool & bigger, const bool & orEqual = false) {
            return bigger ? (orEqual ? a >= b : a > b) : (orEqual ? a <= b : a < b);
        };

        // compare digits number
        if(compare(this->digits.size(), n.getDigits().size(), bigger)) return true;
        if(compare(this->digits.size(), n.getDigits().size(), !bigger)) return false;

        // if both numbers have same digits number, compare each digit
        bool allEqual = true;
        for(auto i = this->digits.rbegin(), j = n.getDigits().rbegin(); i != this->digits.rend(); i++, j++) {
            if(compare(*i, *j, bigger, orEqual)){
                if(*i != *j) return true;
                else if(*i != *j) allEqual = false;
            }
            else {
                if(*i == *j) continue;
                return false;
            }
        }

        // if numbers are equal check orEqual flag
        return !allEqual || orEqual;
    }

    template<class B>
    const bool number<B>::isBigger(const number<B> & a, const bool & orEqual) const {
        return this->makeComparison(a, true, orEqual);
    }

    template<class B>
    const bool number<B>::operator>(const number<B> & a) const {
        return this->isBigger(a);
    }

    template<class B>
    const bool number<B>::isBiggerOrEqual(const number<B> & a) const {
        return this->isBigger(a, true);
    }

    template<class B>
    const bool number<B>::operator>=(const number<B> & a) const {
        return this->isBiggerOrEqual(a);
    }

    template<class B>
    const bool number<B>::isSmaller(const number<B> & a, const bool & orEqual) const {
        return this->makeComparison(a, false, orEqual);
    }

    template<class B>
    const bool number<B>::operator<(const number<B> & a) const {
        return this->isSmaller(a);
    }

    template<class B>
    const bool number<B>::isSmallerOrEqual(const number<B> & a) const {
        return this->isSmaller(a, true);
    }

    template<class B>
    const bool number<B>::operator<=(const number<B> & a) const {
        return this->isSmallerOrEqual(a);
    }

    template<class B>
    const bool number<B>::isEqual(const number<B> & n) const {
        number<B>::assertHaveSameBases(*this, n);

        // check signs
        if(this->isNegative() != n.isNegative()) return false;

        if(this->digits.size() == n.getDigits().size()) {
            for(auto i = this->digits.begin(), j = n.getDigits().begin(); i != this->digits.end(); i++, j++)
                if(*i != *j) return false;
            return true;
        } else return false;
    }

    template<class B>
    const bool number<B>::operator==(const number<B> & a) const {
        return this->isEqual(a);
    }

    template<class B>
    const bool number<B>::operator!=(const number<B> & a) const {
        return !this->isEqual(a);
    }
}
