cmake_minimum_required(VERSION 3.10)
project(GA_EAX_Restart)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -O3")
file(GLOB_RECURSE MATH_LIB_SRC
        src/*.cpp
        )
add_library(math STATIC ${MATH_LIB_SRC})

add_executable(GA_EAX_Restart src/main.cpp)
target_link_libraries(GA_EAX_Restart  math)
