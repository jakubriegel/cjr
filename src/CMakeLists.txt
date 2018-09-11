add_library(
        cjr ""
        ${CMAKE_CURRENT_LIST_DIR}/exceptions/exception.hpp
        ${CMAKE_CURRENT_LIST_DIR}/exceptions/numberExceptions.hpp
        ${CMAKE_CURRENT_LIST_DIR}/cjr.hpp
        ${CMAKE_CURRENT_LIST_DIR}/numbers/utils.hpp numbers/implementation/numberComparison.cpp numbers/implementation/numberAddSubtract.cpp numbers/implementation/numberUtils.cpp numbers/implementation/numberMultiplyDivide.cpp)

target_sources(
        cjr
        PRIVATE
        numbers/implementation/number.cpp
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/numbers/number.hpp
        ${CMAKE_CURRENT_LIST_DIR}/exceptions/exception.hpp
        ${CMAKE_CURRENT_LIST_DIR}/exceptions/numberExceptions.hpp
)

target_include_directories(
        cjr
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)
