cmake_minimum_required(VERSION 3.5)

project(OtusHomework_2_IpSorter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(OtusHomework_2_IpSorter main.cpp)

install(TARGETS OtusHomework_2_IpSorter
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
