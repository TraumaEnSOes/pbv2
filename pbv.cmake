add_library( pbv STATIC
    src/AsyncSupport.cpp
    src/Dependence.cpp
    src/Rules.cpp
    src/TracesStore.cpp
)

install( FILES
    include/pbv/AsyncSupport.hpp
    include/pbv/Counting.hpp
    include/pbv/Embbeded.hpp
    include/pbv/Evaluable.hpp
    include/pbv/Expression.hpp
    include/pbv/Null.hpp
    include/pbv/Rules.hpp
    include/pbv/Sets.hpp
    include/pbv/StaticTrace.hpp
    include/pbv/TracesStore.hpp
    include/pbv/TypeTraits.hpp
    include/pbv/ValidationResult.hpp
    include/pbv/Validator.hpp
    DESTINATION include/pbv
)
