cmake_minimum_required (VERSION 3.0)
project(CBReader)

set( MAKE_CXX_FLAGS "wx-config --cxxflags --libs -Wall" )

##############
## EXTERNAL ##
##############
add_subdirectory(external)


##############
## PROJECT ##
##############

file(GLOB_RECURSE FILES
  src/*
  )

include_directories(include)

add_executable(cbreader ${FILES})

target_link_libraries(cbreader)

target_include_directories(cbreader
  SYSTEM PUBLIC
  external/wxWidgets/include
)