#include "FakeProto.hpp"

#include "pbv/Validator.hpp"
#include "pbv/Embbeded.hpp"

#include <catch2/catch_test_macros.hpp>

namespace EmbbededTest {

class EmbbededValidator : public pbv::Validator< protos::Embbeded > {
    pbv::ValidationResult doValidation( const PROTO *proto ) const override;
};

pbv::ValidationResult EmbbededValidator::doValidation( const PROTO *proto ) const {
    using namespace pbv;

    return ValidationResult( true );
}


class MainValidator : public pbv::Validator< protos::Main > {
    pbv::ValidationResult doValidation( const PROTO *proto ) const override;
};

pbv::ValidationResult MainValidator::doValidation( const PROTO *proto ) const {
    using namespace pbv;

    void AsyncPrologue( );

    Optional singleEmbbeded( proto, OptionallyValidEmbbeded< EmbbededValidator >( "hasSingleEmbbeded", &PROTO::hasSingleEmbbeded, &PROTO::singleEmbbeded ) );

    void AsyncEpilogue( );

    ValidationResult result( singleEmbbeded );

    return result;
}

} // namespace EmbbededTest.

TEST_CASE( "InSet", "[sets]" ) {
    protos::Main mainProto;
    EmbbededTest::MainValidator mainProtoValidator;

    auto result = mainProtoValidator.validate( mainProto );

    REQUIRE( result.result == true );
}