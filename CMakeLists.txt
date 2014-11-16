#Next three lines are pretty self explanatory 
cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_COMPILER "clang++")
set (CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -g3 -std=c++11")

#Creates our project
project (cse555)

#Create our executable Lesson1 from the source file answer.cpp
add_executable(cse555 src/main.cpp)
TARGET_LINK_LIBRARIES(cse555 boost_system)
