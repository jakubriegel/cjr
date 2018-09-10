#pragma once

namespace cjr {
        /// \brief a class defining ranges of bases for \ref number
        /// \details It is used as a template parameter for \ref number. The maximal values of bases are calculated inside \ref number.
        class baseRange final {
        public:
            /// \warning NOT YET IMPLEMENTED
            /// \details baseRange for storing binary numbers
            using binary = bool;
            using small = short int;
            using medium = int;
            using big = long int;
            using huge = long long int;

            virtual ~baseRange() = 0;

            template<class B>
            const static std::string getRangeName(const B & givenBase, const bool & extended = false) {

                const auto type = typeid(givenBase).name();
                std::string response = extended ? "cjr::number::baseRange::" : "";

                if(type == typeid(binary(1)).name()) response += "binary";
                if(type == typeid(small(1)).name()) response += "small";
                if(type == typeid(medium(1)).name()) response += "medium";
                if(type == typeid(big(1)).name()) response += "big";
                if(type == typeid(huge(1)).name()) response += "huge";

                return response;
            }
        };
}