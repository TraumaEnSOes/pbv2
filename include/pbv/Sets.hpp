#ifndef PBV_SETS_HPP
#define PBV_SETS_HPP

#include "pbv/Evaluable.hpp"
#include "pbv/StaticTrace.hpp"
#include "pbv/TracesStore.hpp"

#include <cassert>

namespace pbv {

template< typename PROTO, typename TYPE, typename SET > Evaluable< PROTO > InSet( const char *fieldName, TYPE (PROTO::*getter)( ) const, const SET &set ) {
    auto lambda = [fieldName, getter, set]( const PROTO *proto ) {
        StaticTrace trace;
        const auto &value = (proto->*getter)( );
        ValidationResult result( set.find( value ) != set.end( ) );

        trace << fieldName;

        if( result ) {
            trace = "InSet: ";
            trace << fieldName << " has invalid value";
            result.traces.error( trace );
        } else {
            trace = "Success InSet ";
            trace << fieldName;
        }

        return result;
    };

    assert( !set.empty( ) );

    return lambda;
}

} // namespace pbv.

#endif
