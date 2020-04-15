[![Total alerts](https://img.shields.io/lgtm/alerts/g/wtlgo/Network.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/wtlgo/Network/alerts/)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/wtlgo/Network.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/wtlgo/Network/context:cpp)

# Network

Simple CURL wrapper for general usage

# How to use

 1. Add it to your CMakeLists.txt
 ```Cmake
cmake_minimum_required(VERSION 3.13)
project(your_proj)
include(ExternalProject)

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

ExternalProject_Add(NetworkDownload
    GIT_REPOSITORY https://github.com/wtlgo/Network.git
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)

include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

add_executable(your_target main.cpp)
target_compile_features(your_target PRIVATE cxx_std_17)
add_dependencies(your_target NetworkDownload)
target_link_libraries(your_target Network)
```

 2. Use it
```C++
#include <iostream>
#include <wtlgo/Network.hpp>

int main() {
    using namespace wtlgo;

    std::cout << network.request("http://httpbin.org/ip") << std::endl;

    return 0;
}
```
 3. ????
 2. PROFIT
