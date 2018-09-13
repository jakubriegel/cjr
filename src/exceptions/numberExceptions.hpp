#pragma once

#include "cjr.hpp"
#include "exceptions/exception.hpp"
#include "numbers/utils.hpp"
#include "numbers/number.hpp"

/// \file numberExceptions.hpp
/// \brief Contains custom exceptions for \ref number

namespace cjr {
    namespace exception {

        /// \brief Exception to be thrown when given base is invalid
        /// \details Base is invalid when it is less or equal to zero or it exceed base maximum.
        class invalidBaseException : public exception {
        public:
            template <class B>
            invalidBaseException(const B & givenBase, const B & maxBase)
                : exception(
                        "invalid base assigned to cjr::number<cjr::number::baseRange::" + baseRange::getRangeName(givenBase) + ">: " + std::to_string(givenBase)
                        + ", it should fit in (0," +  std::to_string(maxBase) + "]"
                        ) {}
        };

        /// \brief Exception to be thrown when two numbers have different bases
        class differentBaseException : public exception {
        public:
            differentBaseException() : exception("cjr::numbers have different bases") {}
        };

        /// \brief Exception to be thrown when division by 0 occurs
        class divisionByZeroException : public exception {
        public:
            divisionByZeroException() : exception(
                    "cjr::number to be divided by 0"
                    ) {};
        };
    }
}

