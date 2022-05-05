add_executable( test
#    tests/Embbeded.cpp
#    tests/InSet.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/Null.cpp
)

add_dependencies( test pbv )
target_link_libraries( test pbv ${CONAN_LIBS} )
