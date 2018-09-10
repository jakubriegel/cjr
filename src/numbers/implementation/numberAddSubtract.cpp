
#include <numbers/number.hpp>

#include "numbers/number.hpp"

namespace cjr {
    template <class B>
    void number<B>::addAt(digitIterator i, const B & baseToUse, const B & valueToAdd) {
        // if current range was exceeded append new digit
        if(i == this->digits.end()) {
            this->digits.push_back(0);
            i = std::prev(this->digits.end());
        }

        // add value to the number and process offload
        const B newValue = *i + valueToAdd;
        this->calculateValueAndProceedOffload(i, newValue, baseToUse);
    }

    template <class B>
    void number<B>::subtractAt(digitIterator i, const B & baseToUse, const B & valueToSubtract) {
        while(*i < valueToSubtract) {
            auto next = std::next(i);
            while(*next <= 0) next = std::next(next);
            (*next)--;
            *i += std::pow(baseToUse, std::distance(i, next));
        }

        const B newValue = *i - valueToSubtract;
        this->calculateValueAndProceedOffload(i, newValue, baseToUse);

        while(*std::prev(this->digits.end()) == 0 && this->digits.size() > 1) this->digits.pop_back();
    }

    template <class B>
    void number<B>::calculateValueAndProceedOffload(digitIterator & i, const B & newValue, const B & baseToUse) {
//        baseToUse = (baseToUse == -1) ? this->base : baseToUse;
        if(newValue >= baseToUse) {
            *i = newValue % baseToUse;
            const B offload = (newValue - *i) / baseToUse;
            if(offload > 0) this->addAt(std::next(i), this->base, offload);
        } else *i = newValue;
    }

    template <class B>
    void number<B>::makeCalculations(
            void (number<B>::* calcFunction)(digitIterator, const B &, const B &),
            const digitList & extraDigits, const B & baseToUse) {
        for(B i = 0; i < extraDigits.size(); i++) {
            if(i < this->digits.size()) (this->*calcFunction)(std::next(this->digits.begin(), i), baseToUse,*std::next(extraDigits.begin(), i));
            else this->digits.push_back(*std::next(extraDigits.begin(), i));
        }
    }

    template <class B>
    void number<B>::increment() {
       this->add(number<B>::ONE);
    }

    template<class B>
    void number<B>::operator++() {
        this->increment();
    }

    template<class B>
    const number<B> number<B>::operator++(number<B>) {
        const auto thisBeforeIncrementation = number<B>(*this);
        this->increment();

        return thisBeforeIncrementation;
    }

    template <class B>
    void number<B>::add(const number<B> & numberToAdd) {
        this->add(numberToAdd, this->base);
    }

    template<class B>
    number<B> number<B>::operator+(const number<B> & numberToAdd) const {
        auto result = number<B>(*this);
        result.add(numberToAdd);

        return result;
    }

    template<class B>
    void number<B>::add(const number<B> & numberToAdd, const B & baseToUse) {
        number::assertHaveSameBases(*this, numberToAdd);

        if(numberToAdd.isNegative()) this->subtract(numberToAdd.absoluteValue());
        else {
            if(this->isNegative()) {
                auto temp = numberToAdd;
                temp.subtract(this->absoluteValue(), temp.getBase() == 0 ? this->base : temp.getBase());
                this->setValue(temp);
            }
            else this->makeCalculations(&number<B>::addAt, numberToAdd.getDigits(), baseToUse);
        }
    }

    template <class B>
    void number<B>::add(const B & valueToAdd) {
        if(valueToAdd < 0) this->subtract(std::abs(valueToAdd));
        else if(!this->isNegative()) this->addAt(this->digits.begin(), this->base, valueToAdd);
        else this->add(number<B>(valueToAdd, this->base));
    }

    template<class B>
    number<B> number<B>::operator+(const B & valueToAdd) const {
        auto result = number<B>(*this);
        result.add(valueToAdd);

        return result;
    }

    template <class B>
    void number<B>::decrement() {
        this->subtract(number<B>::ONE);
    }

    template<class B>
    void number<B>::operator--() {
        this->decrement();
    }

    template<class B>
    const number<B> number<B>::operator--(number<B>) {
        const auto thisBeforeDecrementation = number<B>(*this);
        this->decrement();

        return thisBeforeDecrementation;
    }

    template <class B>
    void number<B>::subtract(const number<B> & numberToSubtract) {
        subtract(numberToSubtract, this->base);
    }

    template<class B>
    number<B> number<B>::operator-(const number<B> & numberToSubtract) const {
        auto result = number<B>(*this);
        result.subtract(numberToSubtract);

        return result;
    }

    template<class B>
    void number<B>::subtract(const number<B> & numberToSubtract, const B & baseToUse) {
        number::assertHaveSameBases(*this, numberToSubtract);

        if(*this == numberToSubtract) this->setValue(0);
        else if(numberToSubtract.isNegative()) {
            auto temp = numberToSubtract.absoluteValue();
            this->add(temp);
        }
        else {
            if(this->isNegative()) {
                auto temp = this->absoluteValue();
                temp.add(numberToSubtract);
                this->setValue(temp);
                this->revertSign();
            }
            else {
                if(*this < numberToSubtract) {
                    auto temp = numberToSubtract;
                    temp.subtract(*this, temp.getBase() == 0 ? this->base : temp.getBase());
                    this->setValue(temp);
                    this->revertSign();
                }
                else {
                    this->makeCalculations(&number<B>::subtractAt, numberToSubtract.getDigits(), baseToUse);
                }
            }
        }
    }

    template <class B>
    void number<B>::subtract(const B & valueToSubtract) {
        this->subtract(number<B>(valueToSubtract, this->base));
    }

    template<class B>
    number<B> number<B>::operator-(const B & valueToSubtract) const {
        auto result = number<B>(*this);
        result.subtract(valueToSubtract);

        return result;
    }
}

