cmake_minimum_required(VERSION 3.15)

include_guard(GLOBAL)

project(Network LANGUAGES CXX)

find_package(CURL REQUIRED)
find_package(Boost 1.70.0 REQUIRED)

include_directories(include ${Boost_INCLUDE_DIR} ${CURL_INCLUDE_DIR})

add_library(Network STATIC src/Network.cpp)
target_compile_features(Network PRIVATE cxx_std_17)
target_link_libraries(Network PRIVATE ${Boost_LIBRARIES} ${CURL_LIBRARIES})
target_include_directories(Network PUBLIC ${PROJECT_SOURCE_DIR}/include)

set_property(GLOBAL PROPERTY Network_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(Network PROPERTIES
VERSION 1.0.0
PUBLIC_HEADER "include/Network.hpp")

INSTALL(TARGETS Network 
        LIBRARY DESTINATION Network/lib
        PUBLIC_HEADER DESTINATION Network/include
)
