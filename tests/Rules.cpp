#include "pbv/Rules.hpp"

#include <catch2/catch.hpp>

namespace {

struct FakeProto { };

using Optional = pbv::details::OptionalRule< FakeProto >;

static FakeProto StaticProtoInstance;

} // namespace.

// Single expression, without dependences

TEST_CASE( "SNDOptionalRule" ) {

}

// Single expression, dependence of another rule

// Some expressions, without dependences

// Some expressions, dependence of another rule

