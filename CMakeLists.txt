cmake_minimum_required (VERSION 2.8)
project (Tutorial)

FIND_PACKAGE(PythonInterp)
FIND_PACKAGE(PythonLibs)
FIND_PACKAGE(Boost 1.5.4 COMPONENTS python)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(SDL2 REQUIRED)
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
include_directories(${SDL2_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})

PYTHON_ADD_MODULE(sdlapp src/SDL2Application.cpp)
target_link_libraries(sdlapp ${SDL2_LIBRARY} ${SDL2IMAGE_LIBRARIES})
target_link_libraries(sdlapp ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
