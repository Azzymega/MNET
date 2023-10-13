cmake_minimum_required(VERSION 3.14)
project(rolo)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
file(GLOB gcSource
     "*.hpp"
     "*.cpp"
)
add_library(Rolo SHARED ${gcSource})
