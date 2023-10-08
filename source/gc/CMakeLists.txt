cmake_minimum_required(VERSION 3.14)
project(mgc)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
file(GLOB gcSource
     "*.hpp"
     "*.cpp"
)
add_library(mgc SHARED ${gcSource})
