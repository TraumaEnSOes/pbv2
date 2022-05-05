add_executable( test
    tests/InSet.cpp
    tests/Embbeded.cpp
)

add_dependencies( test pbv )
target_link_libraries( test pbv Catch2::Catch2WithMain )
