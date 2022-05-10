#ifndef PBV_SETS_HPP
#define PBV_SETS_HPP

#include "pbv/Evaluable.hpp"
#include "pbv/StaticTrace.hpp"
#include "pbv/TracesStore.hpp"
#include "pbv/TypeTraits.hpp"

#include <cassert>
#include <unordered_set>

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

    static_assert( std::is_arithmetic_v< TYPE > || std::is_same_v< std::string, details::RemoveCVRefType< TYPE > > );
    static_assert( !std::is_same_v< bool, TYPE >, "It makes no sense to search for a bool in a Set" );
    assert( !set.empty( ) );

    return lambda;
}

template< typename PROTO, typename TYPE, typename SET, typename EPSILON > Evaluable< PROTO > InSet( const char *fieldName, TYPE (PROTO::*getter)( ) const, const SET &set, EPSILON epsilon ) {
    auto lambda = [fieldName, getter, set, epsilon]( const PROTO *proto ) {
        StaticTrace trace;
        const auto &value = (proto->*getter)( );
        ValidationResult result( set.find( value, epsilon ) != set.end( ) );

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

    static_assert( std::is_floating_point_v< TYPE > );
    static_assert( std::is_same_v< TYPE, pbv::details::RemoveCVRefType< EPSILON > >, "The type of the value and the epsilon must coincide" );
    static_assert( !std::is_same_v< SET, std::unordered_set< TYPE > >, "Do not use 'std::unordered_set< >' to store floating point" );

    assert( !set.empty( ) );

    return lambda;
}

} // namespace pbv.

#endif
