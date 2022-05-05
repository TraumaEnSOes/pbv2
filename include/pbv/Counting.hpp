#ifndef PBV_COUNTING_HPP
#define PBV_COUNTING_HPP

#include "pbv/Evaluable.hpp"
#include "pbv/ValidationResult.hpp"

#include <cassert>

namespace pbv {

template< typename PROTO > Evaluable< PROTO > Has( const char *fieldName, int (PROTO::*counter)( ) const, int min = 1, int max = 0 ) {
    auto lambda = [fieldName, counter, min, max]( const PROTO *proto ) {
        ValidationResult result( true );

        result.traces.info( std::string( "Do Has( ) in " ) + fieldName );

        auto count = (proto->*counter)( );

        if( count < min ) {
            result.result = false;
            result.traces.error( std::string( fieldName ) + ": has( ) less than the minimun" );
        } else if( ( max != 0 ) && ( count > max ) ) {
            result.result = false;
            result.traces.error( std::string( fieldName ) + ": has( ) greater than the maximum" );
        }

        return result;
    };

    assert( min > 0 );
    assert( min <= max );

    return lambda;
}

template< typename PROTO > Evaluable< PROTO > Has( const char *fieldName, bool (PROTO::*has)( ) const, int min = 1, int max = 1 ) {
    auto lambda = [fieldName, has]( const PROTO *proto ) {
        ValidationResult result( (proto->*has)( ) );

        result.traces.info( std::string( "Do Has( ) in " ) + fieldName );

        if( !result ) {
            result.result = false;
            result.traces.error( std::string( fieldName ) + ": has( ) less than the minimun" );
        }

        return result;
    };

    assert( min == 1 );
    assert( ( max == 0 ) || ( max == 1 ) );

    return lambda;
}

} // namespace pbv.

#endif
