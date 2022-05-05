add_executable( test
#    tests/Embbeded.cpp
#    tests/InSet.cpp
    tests/Null.cpp
)

add_dependencies( test pbv )
target_link_libraries( test pbv Catch2::Catch2WithMain )
