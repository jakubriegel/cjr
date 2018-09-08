#ifndef CJR_LIB_UTILS_HPP
#define CJR_LIB_UTILS_HPP

namespace cjr {
    class baseRange {
    public:
        using binary = bool;
        using small = short int;
        using medium = int;
        using big = long int;
        using huge = long long int;

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

#endif //CJR_LIB_UTILS_HPP
