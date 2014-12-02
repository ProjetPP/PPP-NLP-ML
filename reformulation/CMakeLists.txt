cmake_minimum_required(VERSION 2.8)
ADD_DEFINITIONS(
    -std=c++0x
    -g
    -Wall
    #-Wextra -pedantic-errors -Werror -Wfatal-errors -Wcast-qual -Wcast-align -Wconversion -Wdouble-promotion -Wfloat-equal -Wshadow -Wpointer-arith -Woverloaded-virtual -Wstrict-aliasing -Wstrict-overflow -Wunsafe-loop-optimizations -Wconversion -Wlogical-op -Wdisabled-optimization -Wunused
    #  -Weffc++ -Wold-style-cast
    -Wno-unknown-warning-option
)
project(reformulation)
add_library(reformulation SHARED
  reformulation/reformulation.cpp
  reformulation/Request.cpp
  reformulation/Dictionary.cpp
  reformulation/Functions.cpp
  reformulation/Transformator.cpp
  reformulation/Trainer.cpp
  reformulation/SemanticNorm.cpp
  reformulation/pyext.cpp)
find_package(PythonLibs 3 REQUIRED)
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
