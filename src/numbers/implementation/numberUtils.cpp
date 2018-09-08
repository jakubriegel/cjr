
#include <numbers/number.hpp>

#include "numbers/number.hpp"

namespace cjr {

    template<class B>
    void number<B>::setValue(const number<B> & a) {
        this->digits = digitList(a.getDigits());
        this->negative = a.isNegative();
    }

    template<class B>
    void number<B>::setValue(const B & newValue) {
        this->digits = digitList();
        this->digits.push_back(0);
        if(newValue != 0) this->add(newValue);
        this->negative = (newValue < 0);
    }

    template<class B>
    const bool number<B>::isZero() const {
        if(this->digits.size() != 1) return false;
        return *(this->digits.begin()) == 0;
    }

    template<class B>
    const number<B> number<B>::absoluteValue() const {
        auto absoluteValue = number<B>(*this);
        absoluteValue.negative = false;
        return absoluteValue;
    }

    template<class B>
    const number<B> number<B>::makeOne() {
        return number<B>(1, true);
    }

    template <class B>
    const std::string number<B>::toString(const bool & withSeparators) const {
        std::string numberString = this->negative ? "-" : "";
        for(auto i = this->digits.rbegin(); i != this->digits.rend(); i++)
            numberString += std::to_string(*i) + (withSeparators ? "`" : "");
        return numberString;
    }

    template <class B>
    void number<B>::print(const bool & withSeparators) const {
        std::cout << this->toString(withSeparators) << std::endl;
    }

    template <class B>
    const B & number<B>::assertBaseIsValid(const B & givenBase) {
        if(givenBase <= 0 || givenBase > number<B>::MAX_BASE) throw exception::invalidBaseException(givenBase, number<B>::MAX_BASE);
        return givenBase;
    }
}

