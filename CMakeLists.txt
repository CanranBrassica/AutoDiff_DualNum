cmake_minimum_required(VERSION 3.5)

project(AutoDiff_DualNum)

set(CMAKE_CXX_STANDARD 17)

add_executable(AutoDiff_DualNum main.cpp AutoDiff.hpp DualNum.hpp)
