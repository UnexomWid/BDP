cmake_minimum_required(VERSION 3.0)
project(bdp)

set(CMAKE_CXX_STANDARD 17)

set(src bdp.cpp bdp.h)

add_library(bdp SHARED ${src})
add_library(bdp_static STATIC ${src})