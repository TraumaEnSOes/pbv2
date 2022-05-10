#include "pbv/Sets.hpp"

#include <catch2/catch.hpp>

#include <unordered_set>

namespace {

template< typename T > struct FakeProto {
    FakeProto( ) = delete;
    FakeProto( T v ) : value( v ) { }

    T getter( ) const noexcept { return value; }

    T value;
};

template< > struct FakeProto< std::string > {
    FakeProto( ) = delete;
    FakeProto( const char *msg ) : value( msg ) { }

    const std::string &getter( ) const noexcept { return value; }

    std::string value;
};

} // namespace

TEST_CASE( "IntegerInSetTest" ) {
    using PROTO = ::FakeProto< int >;

    std::unordered_set< int > ValidsValues( { 1, 3, 5, 7 } );

    PROTO proto1( 5 );
    auto exp = pbv::InSet( "integer", &PROTO::getter, ValidsValues );
    auto result = exp( &proto1 );

    REQUIRE( result.result == true );

    PROTO proto2( 10 );
    result = exp( &proto2 );
    REQUIRE( result.result == false );
}

TEST_CASE( "LongInSetTest" ) {
    using PROTO = ::FakeProto< long >;

    std::unordered_set< long > ValidsValues( { 1L, 3L, 5L, 7L } );

    PROTO proto1( 5L );
    auto exp = pbv::InSet( "long", &PROTO::getter, ValidsValues );
    auto result = exp( &proto1 );

    REQUIRE( result.result == true );

    PROTO proto2( 10L );
    result = exp( &proto2 );
    REQUIRE( result.result == false );
}

TEST_CASE( "LongLongInSetTest" ) {
    using PROTO = ::FakeProto< long long >;

    std::unordered_set< long long > ValidsValues( { 1LL, 3LL, 5LL, 7LL } );

    PROTO proto1( 5LL );
    auto exp = pbv::InSet( "longlong", &PROTO::getter, ValidsValues );
    auto result = exp( &proto1 );

    REQUIRE( result.result == true );

    PROTO proto2( 10LL );
    result = exp( &proto2 );
    REQUIRE( result.result == false );
}

TEST_CASE( "FloatInSetTest" ) {
    using PROTO = ::FakeProto< float >;

    std::unordered_set< float > ValidsValues( { 1.0f, 3.0f, 5.0f, 7.0f } );

    PROTO proto1( 5.0f );
    auto exp = pbv::InSet( "float", &PROTO::getter, ValidsValues );
    auto result = exp( &proto1 );

    REQUIRE( result.result == true );

    PROTO proto2( 10.0f );
    result = exp( &proto2 );
    REQUIRE( result.result == false );
}

TEST_CASE( "DoubleInSetTest" ) {
    using PROTO = ::FakeProto< double >;

    std::unordered_set< double > ValidsValues( { 1.0, 3.0, 5.0, 7.0 } );

    PROTO proto1( 5.0 );
    auto exp = pbv::InSet( "double", &PROTO::getter, ValidsValues );
    auto result = exp( &proto1 );

    REQUIRE( result.result == true );

    PROTO proto2( 10.0 );
    result = exp( &proto2 );
    REQUIRE( result.result == false );
}

TEST_CASE( "StringInSetTest" ) {
    using PROTO = ::FakeProto< std::string >;

    std::unordered_set< std::string > ValidsValues( { "1", "3", "5", "7" } );

    PROTO proto1( "5" );
    auto exp = pbv::InSet( "string", &PROTO::getter, ValidsValues );
    auto result = exp( &proto1 );

    REQUIRE( result.result == true );

    PROTO proto2( "10" );
    result = exp( &proto2 );
    REQUIRE( result.result == false );
}
