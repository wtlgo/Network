
# Network
Simple CURL wrapper for general usage

# How to use

 1. Add it to your CMakeLists.txt
 ```Cmake
 cmake_minimum_required(VERSION 3.15)

project(youtproj)

include(ExternalProject)

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

ExternalProject_Add(NetworkDownload
GIT_REPOSITORY https://github.com/wtlgo/Network.git
CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)

include_directories(${EXTERNAL_INSTALL_LOCATION}/Network/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/Network/lib)

add_executable(your_target main.cpp)
target_compile_features(your_target PUBLIC cxx_std_17)
add_dependencies(your_target NetworkDownload)
target_link_libraries(your_target Network)
```
 2. Use it
```C++
#include  <iostream>
#include  <Network.hpp>  

int  main() {
	std::cout <<  Network::getInstance().request("https://google.com/") <<  std::endl;
	return  0;
}
```
 3. ????
 2. PROFIT
