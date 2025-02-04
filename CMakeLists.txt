
cmake_minimum_required(VERSION 3.10)
project( Task-Tracker )
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include_directories(include)
set(SOURCES src/main.cpp  src/TaskTracker.cpp)
add_executable(Task-Tracker ${SOURCES})