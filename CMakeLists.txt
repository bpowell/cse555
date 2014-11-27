cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_COMPILER "clang++")

#Creates our project
project (cse555)
set (CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -g3 -std=c++11")

IF(APPLE)
        #SET(GUI_TYPE MACOSX_BUNDLE)
        INCLUDE_DIRECTORIES ( /Library/Frameworks/SDL2.framework/ /Library/Frameworks/SDL2_image.framework/)
        FIND_LIBRARY(SDL2_LIB SDL2)
        FIND_LIBRARY(SDL2_IMG_LIB SDL2_image)
        MARK_AS_ADVANCED (SDL2_LIB SDL2_IMG_LIB)
        SET(EXTRA_LIBS ${SDL2_LIB} ${SDL2_IMG_LIB})
    ELSE()
        SET(EXTRA_LIBS SDL2 SDL2_image)
ENDIF (APPLE)

add_executable(cse555 src/main.cpp src/Game.cpp src/Screen.cpp src/StructElement.cpp src/Map.cpp src/Morphological.cpp src/Sprite.cpp)
TARGET_LINK_LIBRARIES(cse555 boost_system ${EXTRA_LIBS})
