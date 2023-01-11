cmake_minimum_required(VERSION 3.13)

include_guard(GLOBAL)

project(
        Network 
        LANGUAGES CXX
        VERSION 4.0.0
)

find_package(CURL REQUIRED)

set(PUBLIC_HEADERS
        "include/wtlgo/NetworkOld.hpp"
)

set(SOURCES
        "src/NetworkOld.cpp"
)

add_library(Network ${SOURCES})
target_compile_features(Network PUBLIC cxx_std_17)
target_link_libraries(Network PUBLIC CURL::libcurl)

target_include_directories(Network PUBLIC include/)
target_include_directories(Network PRIVATE include/wtlgo/)


set_target_properties(Network PROPERTIES 
        PUBLIC_HEADER "${PUBLIC_HEADERS}"
        VERSION ${PROJECT_VERSION}
)

install(
        TARGETS Network
        LIBRARY DESTINATION lib/wtlgo COMPONENT Runtime
        ARCHIVE DESTINATION lib/wtlgo COMPONENT Development
        PUBLIC_HEADER DESTINATION include/wtlgo COMPONENT Development
)

if(DEFINED ENABLE_TESTING)
        enable_testing()
        add_subdirectory(test)
endif()
