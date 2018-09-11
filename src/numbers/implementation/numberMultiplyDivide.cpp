#include <numbers/number.hpp>
#include <functional>

namespace cjr {
    template<class B>
    void number<B>::multiply(const number<B> & numberToMultiply) {
        number<B>::assertHaveSameBases(*this, numberToMultiply);

        const auto resultNegative = (this->isNegative() && !numberToMultiply.isNegative()) || (!this->isNegative() && numberToMultiply.isNegative());

        auto result = number<B>();
        unsigned int power = 0;

        for(auto i = this->digits.begin(); i != this->digits.end(); i++) {
            auto partialResult = number<B>();
            unsigned int microPower = 0;
            for(auto j = numberToMultiply.getDigits().begin(); j != numberToMultiply.getDigits().end(); j++) {
                auto microResult = number<B>(*i * *j);
                microResult.timesBase(microPower);
                partialResult.add(microResult);

                microPower++;
            }
            partialResult.timesBase(power);
            result.add(partialResult);

            power++;
        }

        this->setValue(result);
        this->negative = resultNegative;
    }

    template<class B>
    void number<B>::operator*(const number<B> & numberToMultiply) {
        this->multiply(numberToMultiply);
    }

    template<class B>
    void number<B>::multiply(const B & valueToMultiply) {
        this->multiply(number<B>(valueToMultiply, this->base));
    }

    template<class B>
    void number<B>::operator*(const B & valueToMultiply) {
        this->multiply(valueToMultiply);
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
    void number<B>::power(unsigned int power) {
        if(power == 0) this->setValue(1);
        else if(power == 1) return;
        else if(power == 2) this->multiply(*this);
        else this->setValue(number<B>::swiftPower(*this, power));
    }

    template<class B>
    void number<B>::timesBase(unsigned int power) {
        while(power--) this->digits.push_front(0);
    }
}