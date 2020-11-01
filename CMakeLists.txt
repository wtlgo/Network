cmake_minimum_required(VERSION 3.13)

include_guard(GLOBAL)

project(
        Network 
        LANGUAGES CXX
        VERSION 4.0.0
)

find_package(CURL REQUIRED)

add_library(Network 
        src/Network.cpp 
        src/StandardLogger.cpp

        include/wtlgo/Network.hpp
        include/wtlgo/Logger.hpp
        include/wtlgo/StandardLogger.hpp)
target_compile_features(Network PUBLIC cxx_std_17)
target_link_libraries(Network PUBLIC ${CURL_LIBRARIES})

target_include_directories(Network PUBLIC include/)
target_include_directories(Network PRIVATE include/wtlgo/ ${CURL_INCLUDE_DIR})
set_target_properties(Network PROPERTIES 
        PUBLIC_HEADER 
                include/wtlgo/Network.hpp 
                include/wtlgo/Logger.hpp
                include/wtlgo/StandardLogger.hpp
        VERSION ${PROJECT_VERSION}
)

install(
        TARGETS Network
        LIBRARY DESTINATION lib/wtlgo COMPONENT Runtime
        ARCHIVE DESTINATION lib/wtlgo COMPONENT Development
        PUBLIC_HEADER DESTINATION include/wtlgo COMPONENT Development
)

enable_testing()
add_subdirectory(test)
