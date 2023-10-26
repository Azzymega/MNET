cmake_minimum_required(VERSION 3.14)
project(mnet)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
file(GLOB source
     "*.hpp"
     "*.cpp"
)
add_library(Cabinet SHARED ${source})