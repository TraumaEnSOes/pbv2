cmake_minimum_required( VERSION 2.8.12 )

project( ProtoBValidator LANGUAGES CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED On )
set( CMAKE_CXX_EXTENSIONS Off )

include( "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake" )
conan_basic_setup()

include_directories( 
  ${CMAKE_CURRENT_LIST_DIR}/include
  ${Catch2_INCLUDE_DIRS}
)

include( pbv.cmake )
include( tests.cmake )
