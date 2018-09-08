#ifndef CJR_LIB_NUMBEREXCEPTIONS_HPP
#define CJR_LIB_NUMBEREXCEPTIONS_HPP

#include "cjr.hpp"
#include "exceptions/exception.hpp"
#include "numbers/utils.hpp"
#include "numbers/number.hpp"

namespace cjr {
    namespace exception {
        class invalidBaseException : public exception {
        public:

            template <class B>
            invalidBaseException(const B & givenBase, const B & maxBase)
                : exception(
                        "invalid base assigned to cjr::number<cjr::number::baseRange::" + baseRange::getRangeName(givenBase) + ">: " + std::to_string(givenBase)
                        + ", it should fit in (0," +  std::to_string(maxBase) + "]"
                        ) {}
        };

        class differentBaseException : public exception {
        public:
            differentBaseException() : exception("cjr::numbers have different bases") {}
        };
    }
}


#endif //CJR_LIB_NUMBEREXCEPTIONS_HPP
