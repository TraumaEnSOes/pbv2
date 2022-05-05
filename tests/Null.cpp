#define CATCH_CONFIG_MAIN

#include "pbv/Null.hpp"

#include <catch2/catch.hpp>

namespace NullTest {

template< typename T > struct FakeProto {
    FakeProto( T val ) : notDefaultValue( val ) { }

    T getDefault( ) const noexcept { return T{ }; }
    T getNoDefault( ) const noexcept {
        return notDefaultValue;
    }

    T notDefaultValue;
};

struct FakeStringProto {
    std::string storedEmpty;
    std::string storedNotEmpty{ "NotEmptyString" };

    const std::string &getDefault( ) const noexcept { return storedEmpty; }
    const std::string &getNoDefault( ) const noexcept { return storedNotEmpty; }
};

} // namespace NullTest.

TEST_CASE( "bool", "[module]" ) {
    using PROTO = NullTest::FakeProto< bool >;

    PROTO proto( true );

    auto exp = pbv::NotNull( "boolType", &PROTO::getDefault );
    auto result = exp( &proto );

    REQUIRE( !result );

    exp = pbv::NotNull( "boolType", &PROTO::getNoDefault );
    result = exp( &proto );

    REQUIRE( result );
}

TEST_CASE( "int", "[module]" ) {
    using PROTO = NullTest::FakeProto< int >;

    PROTO proto( 10 );

    auto exp = pbv::NotNull( "boolType", &PROTO::getDefault );
    auto result = exp( &proto );

    REQUIRE( !result );

    exp = pbv::NotNull( "boolType", &PROTO::getNoDefault );
    result = exp( &proto );

    REQUIRE( result );
}

TEST_CASE( "long", "[module]" ) {
    using PROTO = NullTest::FakeProto< long >;

    PROTO proto( 10L );

    auto exp = pbv::NotNull( "boolType", &PROTO::getDefault );
    auto result = exp( &proto );

    REQUIRE( !result );

    exp = pbv::NotNull( "boolType", &PROTO::getNoDefault );
    result = exp( &proto );

    REQUIRE( result );
}

TEST_CASE( "long long", "[module]" ) {
    using PROTO = NullTest::FakeProto< long long >;

    PROTO proto( 10LL );

    auto exp = pbv::NotNull( "boolType", &PROTO::getDefault );
    auto result = exp( &proto );

    REQUIRE( !result );

    exp = pbv::NotNull( "boolType", &PROTO::getNoDefault );
    result = exp( &proto );

    REQUIRE( result );
}

TEST_CASE( "float", "[module]" ) {
    using PROTO = NullTest::FakeProto< float >;

    PROTO proto( 10.0f );

    auto exp = pbv::NotNull( "boolType", &PROTO::getDefault );
    auto result = exp( &proto );

    REQUIRE( !result );

    exp = pbv::NotNull( "boolType", &PROTO::getNoDefault );
    result = exp( &proto );

    REQUIRE( result );
}

TEST_CASE( "string", "[module]" ) {
    using PROTO = NullTest::FakeStringProto;

    PROTO proto;

    auto exp = pbv::NotNull( "boolType", &PROTO::getDefault );
    auto result = exp( &proto );

    REQUIRE( !result );

    exp = pbv::NotNull( "boolType", &PROTO::getNoDefault );
    result = exp( &proto );

    REQUIRE( result );
}
