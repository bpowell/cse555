cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_COMPILER "clang++")
set (CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -g3 -std=c++11")

#Creates our project
project (cse555)

IF(APPLE)
        #SET(GUI_TYPE MACOSX_BUNDLE)
        INCLUDE_DIRECTORIES ( /Library/Frameworks/SDL2.framework/ )
        FIND_LIBRARY(SDL2_LIB SDL2)
        MARK_AS_ADVANCED (SDL2_LIB)
        SET(EXTRA_LIBS ${SDL2_LIB})
ENDIF (APPLE)

add_executable(cse555 src/main.cpp src/Game.cpp src/Screen.cpp src/StructElement.cpp src/Map.cpp src/Morphological.cpp)
TARGET_LINK_LIBRARIES(cse555 boost_system ${EXTRA_LIBS})
