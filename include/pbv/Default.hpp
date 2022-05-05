#ifndef PBV_DEFAULT_HPP
#define PBV_DEFAULT_HPP

#include "pbv/Evaluable.hpp"
#include "pbv/StaticTrace.hpp"

#include <string>
#include <type_traits>

namespace pbv {

template< typename PROTO, typename TYPE, typename ENABLED = typename std::enable_if< std::is_arithmetic_v< TYPE >, TYPE >::type > Evaluable< PROTO > IsDefault( const char *fieldName, TYPE (PROTO::*getter)( ) const ) {
    auto lambda = [fieldName, getter]( const PROTO *proto ) {
        ValidationResult result( (proto->*getter)( ) == TYPE{ } );
        StaticTrace trace;

        if( result ) {
            trace = fieldName;
            trace << " IsDefault";
            result.traces.info( trace );
        } else {
            trace = fieldName
            trace << " IsDefault: false";
            result.traces.error( trace );
        }

        return result;
    };

    return lambda;
}

template< typename PROTO > Evaluable< PROTO > IsDefault( const char *fieldName, const std::string &(PROTO::*getter)( ) const ) {
    auto lambda = [fieldName, getter]( const PROTO *proto ) {
        ValidationResult result( (proto->*getter).empty( ) );
        StaticTrace trace;

        if( result ) {
            trace = fieldName;
            trace << " IsDefault string (empty)";
            result.traces.info( trace );
        } else {
            trace = fieldName
            trace << " IsDefault: false (not empty string)";
            result.traces.error( trace );
        }

        return result;
    };

    return lambda;
}

template< typename PROTO, typename TYPE, typename ENABLED = typename std::enable_if< std::is_arithmetic_v< TYPE >, TYPE >::type > Evaluable< PROTO > NoDefault( const char *fieldName, TYPE (PROTO::*getter)( ) const ) {
    auto lambda = [fieldName, getter]( const PROTO *proto ) {
        ValidationResult result( (proto->*getter)( ) != TYPE{ } );
        StaticTrace trace;

        if( result ) {
            trace = fieldName;
            trace << " NoDefault";
            result.traces.info( trace );
        } else {
            trace = fieldName;
            trace << " NoDefault: false, is default value";
            result.traces.error( trace );
        }

        return result;        
    }

    return lambda;
}

template< typename PROTO > Evaluable< PROTO > NoDefault( const char *fieldName, const std::string &(PROTO::*getter)( ) const ) {
    auto lambda = [fieldName, getter]( const PROTO *proto ) {
        ValidationResult result( !( (proto->*getter).empty( ) ) );
        StaticTrace trace;

        if( result ) {
            trace = fieldName;
            trace << " NoDefault string (not empty)";
            result.traces.info( trace );
        } else {
            trace = fieldName
            trace << " NoDefault: false (is empty string)";
            result.traces.error( trace );
        }

        return result;
    };

    return lambda;
}

} // namespace pbv.

#endif
