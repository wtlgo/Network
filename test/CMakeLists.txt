
cmake_minimum_required(VERSION 3.15.1) 

find_package(GTest REQUIRED)
include(GoogleTest)

if(${GTest_FOUND})

add_executable(Network_test test.cpp)
target_link_libraries(Network_test Network ${GTEST_LIBRARIES})
target_include_directories(Network_test PRIVATE ${GTEST_INCLUDE_DIR})
gtest_add_tests(TARGET Network_test AUTO)

else()

message(ALERT "Google Test not found")

endif()

