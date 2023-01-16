cmake_minimum_required(VERSION 3.5)

project(OtusHomework_2_IpSorter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.12.0

)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(OtusHomework_2_IpSorter main.cpp utils.hpp )
add_executable(OtusHomework_2_IpSorter_Test parserTest.cpp utils.hpp)

target_include_directories(OtusHomework_2_IpSorter_Test    PRIVATE "${googletest_SOURCE_DIR}/googletest/include")
target_link_libraries(OtusHomework_2_IpSorter_Test PRIVATE  GTest::GTest  )



install(TARGETS OtusHomework_2_IpSorter
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

#добавление теста
enable_testing()
add_test(UtilsTests tests)
