cmake_minimum_required(VERSION 2.8)
ADD_DEFINITIONS(
    -std=c++11 # Or -std=c++0x
    -g
    -Wall
    -Wextra -pedantic-errors -Werror -Wfatal-errors -Wcast-qual -Wcast-align -Wconversion -Wdouble-promotion -Wfloat-equal -Wshadow -Wpointer-arith -Woverloaded-virtual -Wstrict-aliasing -Wstrict-overflow -Wunsafe-loop-optimizations -Wconversion -Wlogical-op -Wdisabled-optimization -Wunused
    #  -Weffc++ -Wold-style-cast
)
project(reformulation)
add_library(reformulation SHARED
  reformulation/reformulation.cpp
  reformulation/Request.cpp
  reformulation/Dictionary.cpp
  reformulation/Functions.cpp
  reformulation/Transformator.cpp
  reformulation/Trainer.cpp)
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(reformulation pthread ${PYTHON_LIBRARIES})

#install(TARGETS reformulation RUNTIME DESTINATION bin)
