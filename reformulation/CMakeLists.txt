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
  reformulation/Transformator.cpp
  reformulation/Trainer.cpp
  reformulation/pyext.cpp)
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(reformulation pthread ${PYTHON_LIBRARIES})

project(phprefor)
add_library(phprefor SHARED
  reformulation/reformulation.cpp
  reformulation/Request.cpp
  reformulation/Dictionary.cpp
  reformulation/Functions.cpp
  reformulation/Transformator.cpp
  reformulation/Trainer.cpp
  reformulation/phpext.cpp)


target_link_libraries(phprefor pthread phpcpp)
#install(TARGETS reformulation RUNTIME DESTINATION bin)
