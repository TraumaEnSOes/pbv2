cmake_minimum_required( VERSION 2.8.12 )
project( ProtoBValidator LANGUAGES CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED On )
set( CMAKE_CXX_EXTENSIONS Off )

find_package( Catch2 REQUIRED PATHS "${CMAKE_CURRENT_LIST_DIR}/3rdparty/lib/cmake/Catch2" )

include_directories( "${CMAKE_CURRENT_LIST_DIR}/include" )

include( pbv.cmake )
include( tests.cmake )
