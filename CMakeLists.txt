cmake_minimum_required(VERSION 3.15)

include_guard(GLOBAL)

project(
        Network 
        LANGUAGES CXX
        VERSION 3.2.0
)

find_package(CURL REQUIRED)

include_directories(include ${CURL_INCLUDE_DIR})

add_library(Network STATIC src/Network.cpp)
target_compile_features(Network PUBLIC cxx_std_17)
target_link_libraries(Network PUBLIC ${CURL_LIBRARIES})

target_include_directories(Network INTERFACE ${PROJECT_SOURCE_DIR}/include/)
target_include_directories(Network PRIVATE ${PROJECT_SOURCE_DIR}/include/wtlgo/)
set_target_properties(Network PROPERTIES PUBLIC_HEADER ${PROJECT_SOURCE_DIR}/include/wtlgo/Network.hpp)

install(
        TARGETS Network
        LIBRARY DESTINATION lib COMPONENT Runtime
        ARCHIVE DESTINATION lib COMPONENT Development
        PUBLIC_HEADER DESTINATION include/wtlgo COMPONENT Development
)

enable_testing()
add_subdirectory(test)
