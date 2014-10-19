cmake_minimum_required(VERSION 2.8)
ADD_DEFINITIONS(
    -std=c++11 # Or -std=c++0x
    # Other flags
)
project(reformulation)
add_executable(reformulation 
  reformulation/reformulation.cpp
  reformulation/Request.cpp
  reformulation/Dictionary.cpp
  reformulation/Functions.cpp)
export_library_dependencies(reformulation pthread)

install(TARGETS reformulation RUNTIME DESTINATION bin)
