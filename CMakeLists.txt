cmake_minimum_required (VERSION 3.0)
project(CBReader)

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
target_link_libraries(cbreader sfml-window)
target_include_directories(cbreader
  SYSTEM PUBLIC
#   external/SFML/include
  external/SFML
)