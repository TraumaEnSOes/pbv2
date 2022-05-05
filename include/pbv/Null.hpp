#ifndef PBV_NULL_HPP
#define PBV_NULL_HPP

#include "pbv/Evaluable.hpp"
#include "pbv/StaticTrace.hpp"

#include <type_traits>

namespace pbv {

template< typename PROTO, typename T > Evaluable< PROTO > NotNull( const char *fieldName, T (PROTO::*getter)( ) const ) {
    static_assert( std::is_arithmetic_v< T > );

    auto lambda = [fieldName, getter]( const PROTO *proto ) {
        ValidationResult result( (proto->*getter)( ) != T{ } );
        StaticTrace trace( fieldName );

        if( result ) {
            trace << " has not the default value";
            result.traces.info( trace );
        } else {
            trace << " has the default value";
            result.traces.error( trace );
        }

        return result;
    };

    return lambda;
}

template< typename PROTO > Evaluable< PROTO > NotNull( const char *fieldName, const std::string &(PROTO::*getter)( ) const ) {
    auto lambda = [fieldName, getter]( const PROTO *proto ) {
        ValidationResult result( !( (proto->*getter)( ).empty( ) ) );
        StaticTrace trace;

        if( result ) {
            trace << " has not the default value";
            result.traces.info( trace );        
        } else {
            trace << " has the default value";
            result.traces.error( trace );            
        }

        return result;
    };

    return lambda;
}

} // namespace pbv.

#endif
