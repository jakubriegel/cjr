#ifndef CJR_LIB_EXCEPTION_HPP
#define CJR_LIB_EXCEPTION_HPP

#include <exception>
#include <cstring>

namespace cjr {
    namespace exception {
        class exception : public std::exception {
        protected:
            char * message;

        public:
            exception() : message(nullptr) {}

            explicit exception(const std::string & givenMessage) {
                auto * msg = new char[givenMessage.size()];
                std::strcpy(msg, givenMessage.c_str());
                this->message = msg;
            }

            ~exception() override {
                delete this->message;
            }

            const char * what() const noexcept override {
                return this->message;
            }
        };
    }
}

#endif //CJR_LIB_EXCEPTION_HPP
