#include "pbv/Null.hpp"

#include <catch2/catch.hpp>

namespace {

template< typename T > struct FakeProto {
    FakeProto( T val ) : notDefaultValue( val ) { }

    T getDefault( ) const noexcept { return T{ }; }
    T getNoDefault( ) const noexcept {
        return notDefaultValue;
    }

    T notDefaultValue;
};

template< > struct FakeProto< std::string > {
    std::string storedEmpty;
    std::string storedNotEmpty{ "NotEmptyString" };

    const std::string &getDefault( ) const noexcept { return storedEmpty; }
    const std::string &getNoDefault( ) const noexcept { return storedNotEmpty; }
};

} // namespace.

TEST_CASE( "BoolNullTest" ) {
    using PROTO = ::FakeProto< bool >;

    PROTO proto( true );

    auto exp = pbv::NotNull( "boolType", &PROTO::getDefault );
    auto result = exp( &proto );

    REQUIRE( !result );

    exp = pbv::NotNull( "boolType", &PROTO::getNoDefault );
    result = exp( &proto );

    REQUIRE( result );
}

TEST_CASE( "IntNullTest" ) {
    using PROTO = ::FakeProto< int >;

    PROTO proto( 10 );

    auto exp = pbv::NotNull( "intType", &PROTO::getDefault );
    auto result = exp( &proto );

    REQUIRE( !result );

    exp = pbv::NotNull( "intType", &PROTO::getNoDefault );
    result = exp( &proto );

    REQUIRE( result );
}

TEST_CASE( "LongNullTest" ) {
    using PROTO = ::FakeProto< long >;

    PROTO proto( 10L );

    auto exp = pbv::NotNull( "longType", &PROTO::getDefault );
    auto result = exp( &proto );

    REQUIRE( !result );

    exp = pbv::NotNull( "longType", &PROTO::getNoDefault );
    result = exp( &proto );

    REQUIRE( result );
}

TEST_CASE( "LongLongNullTest" ) {
    using PROTO = ::FakeProto< long long >;

    PROTO proto( 10LL );

    auto exp = pbv::NotNull( "longlongType", &PROTO::getDefault );
    auto result = exp( &proto );

    REQUIRE( !result );

    exp = pbv::NotNull( "longlongType", &PROTO::getNoDefault );
    result = exp( &proto );

    REQUIRE( result );
}

TEST_CASE( "FloatNullTest" ) {
    using PROTO = ::FakeProto< float >;

    PROTO proto( 10.0f );

    auto exp = pbv::NotNull( "floatType", &PROTO::getDefault );
    auto result = exp( &proto );

    REQUIRE( !result );

    exp = pbv::NotNull( "floatType", &PROTO::getNoDefault );
    result = exp( &proto );

    REQUIRE( result );
}

TEST_CASE( "DoubleNullTest" ) {
    using PROTO = ::FakeProto< double >;

    PROTO proto( 10.0 );

    auto exp = pbv::NotNull( "doubleType", &PROTO::getDefault );
    auto result = exp( &proto );

    REQUIRE( !result );

    exp = pbv::NotNull( "doubleType", &PROTO::getNoDefault );
    result = exp( &proto );

    REQUIRE( result );
}

TEST_CASE( "LongDoubleNullTest" ) {
    using PROTO = ::FakeProto< long double >;

    PROTO proto( 10.0l );

    auto exp = pbv::NotNull( "longDoubleType", &PROTO::getDefault );
    auto result = exp( &proto );

    REQUIRE( !result );

    exp = pbv::NotNull( "longDoubleType", &PROTO::getNoDefault );
    result = exp( &proto );

    REQUIRE( result );
}

TEST_CASE( "StringNullTest" ) {
    using PROTO = ::FakeProto< std::string >;

    PROTO proto;

    auto exp = pbv::NotNull( "stringType", &PROTO::getDefault );
    auto result = exp( &proto );

    REQUIRE( !result );

    exp = pbv::NotNull( "stringType", &PROTO::getNoDefault );
    result = exp( &proto );

    REQUIRE( result );
}
