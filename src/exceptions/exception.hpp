#pragma once

#include <exception>
#include <cstring>

namespace cjr {
    namespace exception {

        /// \brief Universal exception for cjr
        class exception : public std::exception {
        protected:
            /// \brief Message to be displayed with error
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