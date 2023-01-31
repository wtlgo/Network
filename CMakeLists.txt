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

        "include/wtlgo/network/HttpBasicAuth.hpp"
        "include/wtlgo/network/DefaultHttpBasicAuth.hpp"

        "include/wtlgo/network/HttpMethod.hpp"

        "include/wtlgo/network/Config.hpp"
        "include/wtlgo/network/DefaultConfig.hpp"

        "include/wtlgo/network/Headers.hpp"
        "include/wtlgo/network/HttpHeaders.hpp"
)

set(SOURCES
        "src/NetworkOld.cpp"
        "src/DefaultHttpBasicAuth.cpp"
        "src/DefaultConfig.cpp"
        "src/HttpHeaders.cpp"

        "src/internal/MergedConfig.hpp"
        "src/internal/MergedConfig.cpp"

        "src/internal/CopyOnWriteConfig.hpp"
        "src/internal/CopyOnWriteConfig.cpp"
)

add_library(Network ${SOURCES})
target_compile_features(Network PUBLIC cxx_std_17)
target_link_libraries(Network PUBLIC CURL::libcurl)

target_include_directories(Network PUBLIC include/)
target_include_directories(Network PRIVATE include/)

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
