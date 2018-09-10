
#include <numbers/number.hpp>

#include "numbers/number.hpp"

namespace cjr {

    // definitions of static members

    template <class B>
    const cjr::number<B> number<B>::ONE = cjr::number<B>::makeUniversal(1);

    template <class B>
    const cjr::number<B> number<B>::ZERO = cjr::number<B>::makeUniversal(0);

    template <class B>
    const B number<B>::MAX_BASE = std::sqrt(std::numeric_limits<B>::max() - 1);

    // constructors

    // private
    template<class B>
    number<B>::number(const B & initValue, const bool & zeroBase) : base(0), negative(false){
        this->digits.push_front(initValue);
    }

    template <class B>
    number<B>::number() : base(10), negative(false) {
        this->digits.push_front(0);
    }

    template <class B>
    number<B>::number(const B & initValue, const B & base) : base(number<B>::assertBaseIsValid(base)), negative(false) {
        this->digits.push_front(0);
        if(initValue != 0) this->add(initValue);
    }

    template<class B>
    number<B>::number(const number<B> & sourceNumber)
        : base(sourceNumber.getBase()), digits(sourceNumber.getDigits()), negative(sourceNumber.isNegative()) {}

}

