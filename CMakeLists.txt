cmake_minimum_required(VERSION 3.0)

include_guard(GLOBAL)

project(
        Network 
        LANGUAGES CXX
        VERSION 3.1.1
)

find_package(CURL REQUIRED)

include_directories(include ${CURL_INCLUDE_DIR})

add_library(Network STATIC src/Network.cpp)
target_compile_features(Network PUBLIC cxx_std_17)
target_link_libraries(Network PUBLIC ${CURL_LIBRARIES})

target_include_directories(Network INTERFACE ${PROJECT_SOURCE_DIR}/include/)
target_include_directories(Network PRIVATE ${PROJECT_SOURCE_DIR}/include/wtlgo/)

enable_testing()
add_subdirectory(test)
