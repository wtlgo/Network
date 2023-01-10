cmake_minimum_required(VERSION 3.13) 


include(FetchContent)


FetchContent_Declare(
    json 
    URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


file(GLOB TEST_SRC
    "src/*.cpp"
)

add_executable(Network_test ${TEST_SRC})
target_link_libraries(Network_test Network GTest::gtest_main nlohmann_json::nlohmann_json)

include(GoogleTest)
gtest_discover_tests(Network_test)
