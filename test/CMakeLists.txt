add_executable(
        unit_tests
        numbers/comparisonTest.cpp numbers/addSubtractTest.cpp numbers/generalTest.cpp numbers/utilsTest.cpp)

target_link_libraries(
        unit_tests
        gtest_main
        cjr
)

add_test(
    NAME
        unit
    COMMAND
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
)