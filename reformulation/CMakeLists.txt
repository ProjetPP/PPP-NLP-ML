cmake_minimum_required(VERSION 2.8)
ADD_DEFINITIONS(
    -std=c++11 # Or -std=c++0x
    # Other flags
)
project(reformulation)
add_library(reformulation SHARED
  reformulation/reformulation.cpp
  reformulation/Request.cpp
  reformulation/Dictionary.cpp
  reformulation/Functions.cpp
  reformulation/Transformator.cpp)
link_directories(/usr/lib/python3.4m)
target_link_libraries(reformulation pthread python3.4m)
include_directories(reformulation /usr/include/python3.4m)

#install(TARGETS reformulation RUNTIME DESTINATION bin)
