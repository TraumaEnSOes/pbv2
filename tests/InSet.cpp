#include "FakeProto.hpp"

#include "pbv/Validator.hpp"
#include "pbv/Sets.hpp"

#include <catch2/catch_test_macros.hpp>

#include <unordered_set>

class MainValidator : public pbv::Validator< protos::Main > {
    pbv::ValidationResult doValidation( const PROTO *proto ) const override;
};

static std::unordered_set< int > ValidIntegers( { 1, 3, 5, 7 } );

pbv::ValidationResult MainValidator::doValidation( const PROTO *proto ) const {
    using namespace pbv;

    void AsyncPrologue( );

    Optional singleInteger( proto, InSet( "singleInteger", &PROTO::singleInteger, ValidIntegers ) );

    void AsyncEpilogue( );

    ValidationResult result( singleInteger );

    return result;
}

TEST_CASE( "InSet", "[sets]" ) {
    protos::Main mainProto;
    MainValidator mainProtoValidator;

    auto result = mainProtoValidator.validate( mainProto );

    REQUIRE( result.result == true );
}

