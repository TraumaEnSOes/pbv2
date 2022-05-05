#include "pbv/AsyncSupport.hpp"
#include "pbv/Counting.hpp"
#include "pbv/Sets.hpp"
#include "pbv/Validator.hpp"

#include <unordered_set>

struct Proto {
    bool hasSingle( ) const noexcept { return true; }
    int singleInt( ) const noexcept { return 7; }
    int hasRepeated( ) const noexcept { return 5; }
    int repeatedInt( int idx ) const noexcept { return 7; }
};

template< typename PROTO, bool v > struct FixedExpression {
    pbv::ValidationResult operator( )( const Proto *proto ) {
        return pbv::ValidationResult( v );
    }
};

struct ProtoValidator : public pbv::Validator< Proto > {
    pbv::ValidationResult doValidation( const PROTO *proto ) const override;
};

static std::unordered_set< int > IntegerInSet( { 1, 3, 5, 7 } );

pbv::ValidationResult ProtoValidator::doValidation( const PROTO *proto ) const {
    using namespace pbv;
    
    AsyncPrologue( );

    Optional testRule( proto, FixedExpression< PROTO, false >( ) );

    Optional testHas( proto, {
        Has( "hasSingle", &PROTO::hasSingle ),
        Has( "hasRepeated", &PROTO::hasRepeated ),
        InSet( "repeatedInt", &PROTO::singleInt, IntegerInSet )
    } );

    Optional testComplexRule( proto, {
        FixedExpression< PROTO, true >( ),
        FixedExpression< PROTO, false >( )
    } );

    Optional dependendRule( testRule, proto, FixedExpression< PROTO, true >( ) );

    Optional dependendRule2( testComplexRule == 1, proto, {
        FixedExpression< PROTO, true >( ),
        FixedExpression< PROTO, false >( )
    } );

    AsyncEpilogue( );

    return { 0 };
};

int main( ) {
    Proto proto;
    ProtoValidator validator;

    auto result = validator.validate( proto );

    return result.result;
}