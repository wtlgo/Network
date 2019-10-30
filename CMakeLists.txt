cmake_minimum_required(VERSION 3.15)

include_guard(GLOBAL)

project(Network LANGUAGES CXX)

find_package(CURL REQUIRED)

include_directories(include ${CURL_INCLUDE_DIR})

add_library(Network SHARED src/Network.cpp)
target_compile_features(Network PUBLIC cxx_std_17)
target_link_libraries(Network PRIVATE ${CURL_LIBRARIES})
target_include_directories(Network PUBLIC ${PROJECT_SOURCE_DIR}/include)

set_property(GLOBAL PROPERTY Network_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(Network PROPERTIES
VERSION 2.0.2
PUBLIC_HEADER "include/Network.hpp")

INSTALL(TARGETS Network 
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include/wtlgo/Network
)
