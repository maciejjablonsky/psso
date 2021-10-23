cmake_minimum_required(VERSION 3.15)
project(PSSO_P01 CXX)

if (EXISTS ${CMAKE_BINARY_DIR}/conan_paths.cmake)
    include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
endif()

if(PSSO_TESTING_ENABLED)
    enable_testing()
endif()

add_subdirectory(src)
