#include <numbers/number.hpp>
#include <functional>

namespace cjr {
    template<class B>
    void number<B>::multiply(const number<B> & numberToMultiply) {
        number<B>::assertHaveSameBases(*this, numberToMultiply);

        const auto resultNegative = number<B>::getSignAfterMultiplication(*this, numberToMultiply);

        auto result = number<B>();
        unsigned int power = 0;

        for(auto i = this->digits.begin(); i != this->digits.end(); i++) {
            auto partialResult = number<B>();
            unsigned int microPower = 0;
            for(auto j = numberToMultiply.getDigits().begin(); j != numberToMultiply.getDigits().end(); j++) {
                auto microResult = number<B>(*i * *j);
                microResult.multiplyByBase(microPower);
                partialResult.add(microResult);

                microPower++;
            }
            partialResult.multiplyByBase(power);
            result.add(partialResult);

            power++;
        }

        this->setValue(result);
        this->negative = resultNegative;
    }

    template<class B>
    number<B> number<B>::operator*(const number<B> & numberToMultiply) const {
        auto result = number<B>(*this);
        result.multiply(numberToMultiply);

        return result;
    }

    template<class B>
    void number<B>::multiply(const B & valueToMultiply) {
        this->multiply(number<B>(valueToMultiply, this->base));
    }

    template<class B>
    number<B> number<B>::operator*(const B & valueToMultiply) const{
        auto result = number<B>(*this);
        result.multiply(valueToMultiply);

        return result;
    }

    template<class B>
    number<B> number<B>::swiftPower(number<B> n, unsigned int p) {
        if(p == 0) return number<B>(1, n.getBase());
        if(p % 2 == 1) {
            auto newPower = number<B>::swiftPower(n, (p - 1) / 2);
            newPower.power();
            n.multiply(newPower);
            return n;
        }
        else {
            auto newPower = number<B>::swiftPower(n, p / 2);
            newPower.power();

            return newPower;
        }
    };

    template<class B>
    const bool number<B>::getSignAfterMultiplication(const number<B> & n1, const number<B> & n2) {
        return (n1.isNegative() && !n2.isNegative()) || (!n1.isNegative() && n2.isNegative());;
    }

    template<class B>
    void number<B>::power(unsigned int power) {
        if(power == 0) this->setValue(1);
        else if(power == 1) return;
        else if(power == 2) this->multiply(*this);
        else this->setValue(number<B>::swiftPower(*this, power));
    }

    template<class B>
    void number<B>::multiplyByBase(unsigned int power) {
        if(!this->isZero()) while(power--) this->digits.push_front(0);
    }

    template<class B>
    const number<B> number<B>::integerDivision(const number<B> & dividend, number<B> divisor, const bool & returnRemainder) {
        number<B>::assertHaveSameBases(dividend, divisor);

        auto result = number<B>(0, dividend.base);
        auto remainder = number<B>(0, dividend.base);
        const auto resultNegative = number<B>::getSignAfterMultiplication(dividend, divisor);

        if(divisor.isNegative()) divisor.revertSign();

        for(auto i = dividend.digits.rbegin(); i != dividend.digits.rend(); i++) {
            auto partialDividend = number(0, dividend.base);

            remainder.multiplyByBase();
            remainder.add(*i);

            if(remainder.isZero()) result.multiplyByBase();
            else if(remainder < divisor) result.multiplyByBase();
            else {
                result.multiplyByBase();
                while(remainder >= divisor) {
                    remainder.subtract(divisor);
                    result++;
                }
            }
        }

        result.negative = resultNegative;
        return returnRemainder ? remainder : result;
    }

    template<class B>
    void number<B>::divide(number<B> divisor) {
        number<B>::assertHaveSameBases(*this, divisor);

        if(divisor == number::ZERO) throw exception::divisionByZeroException();
        else if(this->isZero()) this->setValue(0);
        else if(divisor > *this) this->setValue(0);
        else if(*this == divisor) this->setValue(1);
        else if(divisor == number::ONE) return;
        else this->setValue(number<B>::integerDivision(*this, divisor));
    }

    template<class B>
    number<B> number<B>::operator/(const number<B> & divisor) const {
        auto result = number<B>(*this);
        result.divide(divisor);

        return result;
    }

    template<class B>
    void number<B>::divide(const B & divisor) {
        this->divide(number<B>(divisor, this->base));
    }

    template<class B>
    number<B> number<B>::operator/(const B & divisor) const {
        auto result = number<B>(*this);
        result.divide(divisor);

        return result;
    }

    template<class B>
    const number<B> number<B>::remainder(number<B> divisor) const {
        return number<B>::integerDivision(*this, divisor, true);
    }

    template<class B>
    const number<B> number<B>::operator%(number<B> divisor) const {
        return this->remainder(divisor);
    }

    template<class B>
    const number<B> number<B>::divideByBase(unsigned int power) {
        auto result = number<B>(0, this->base);
        if(!this->isZero()) while(power--) {
                result.multiplyByBase();
                result.add(this->digits.back());

                this->digits.pop_back();
                if(this->digits.empty()) {
                    this->digits.push_front(0);
                    break;
                }
        }
        return result;
    }
}