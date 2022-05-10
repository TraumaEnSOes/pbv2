add_executable( test
    tests/main.cpp
#    tests/Embbeded.cpp
    tests/InSet.cpp
    tests/Null.cpp
)

add_dependencies( test pbv )
target_link_libraries( test pbv ${CONAN_LIBS} )
