cmake_minimum_required(VERSION 3.13) 

find_package(GTest)
find_package(nlohmann_json)

include(GoogleTest)

if(${GTest_FOUND} AND ${nlohmann_json_FOUND})

    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    file(GLOB TEST_SRC
        "src/*.hpp"
        "src/*.cpp"
    )

    add_executable(Network_test ${TEST_SRC})
    target_link_libraries(Network_test Network ${GTEST_LIBRARIES} nlohmann_json)
    target_include_directories(Network_test PRIVATE ${GTEST_INCLUDE_DIR})
    gtest_add_tests(TARGET Network_test AUTO)

else()

    message(WARNING "You should install GTest and nlohmann-json to enable tests.")

endif()

