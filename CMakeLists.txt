cmake_minimum_required(VERSION 3.14)
project(mnet)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
file(GLOB mainLib
     "source/*.hpp"
     "source/*.cpp"
)
add_library(mainNet SHARED ${mainLib})
add_executable(mainTest test/mainTest.cpp)
target_link_libraries(mainTest PRIVATE mainNet)