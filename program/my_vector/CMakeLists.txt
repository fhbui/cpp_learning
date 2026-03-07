cmake_minimum_required(VERSION 3.30)
project(my_vector)

set(CMAKE_CXX_STANDARD 17)  

include_directories("inc")

file(GLOB INCLUDES "inc/*.h")
file(GLOB SOURCES "src/*.cpp")

add_executable(app main.cpp ${SOURCES})
