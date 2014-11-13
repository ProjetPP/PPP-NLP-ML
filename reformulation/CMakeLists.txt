cmake_minimum_required(VERSION 2.8)
ADD_DEFINITIONS(
    -std=c++11 # Or -std=c++0x
    -g
    -Wall
    # Other flags
)
project(reformulation)
add_library(reformulation SHARED
  reformulation/reformulation.cpp
  reformulation/Request.cpp
  reformulation/Dictionary.cpp
  reformulation/Functions.cpp
  reformulation/Transformator.cpp)
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(reformulation pthread ${PYTHON_LIBRARIES})

#install(TARGETS reformulation RUNTIME DESTINATION bin)
