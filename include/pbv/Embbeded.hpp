#ifndef PBV_EMBBEDED_HPP
#define PBV_EMBBEDED_HPP

#include "pbv/Expression.hpp"
#include "pbv/StaticTrace.hpp"

namespace pbv {

template< typename VALIDATOR, typename PROTO, typename INNER = typename VALIDATOR::PROTO > Expression< PROTO > OptionallyValidEmbbeded( const char *fieldName, bool (PROTO::*has)( ) const, const INNER &(PROTO::*getter)( ) const ) {
    auto lambda = [fieldName, has, getter]( const PROTO *proto ) {
        ValidationResult result;
        StaticTrace trace;

        result.traces.info( trace );

        if( (proto->*has)( ) ) {
            trace = "Starting validation of optionally embbeded proto: ";
            trace << fieldName;
            result.traces.info( trace );

            {
                VALIDATOR validator;

                auto innerResult = validator.validate( *(proto->*getter)( ) );

                result |= innerResult;
            }

            trace = "Embbeded proto ";
            trace << fieldName;
            if( result.result == true ) {
                trace << " success";
                result.traces.info( trace );
            } else {
                trace << " failled";
                result.traces.error( trace );
            }
        } else {
            trace = "Optionally embbeded ";
            trace << fieldName;
            trace << " absent. Skip it";

            result.result = true;
            result.traces.info( trace );
        }

        return result;
    };

    return lambda;
}

#if 0
template< typename VALIDATOR, typename PROTO, typename INNER = typename VALIDATOR::PROTO > struct ValidEmbbeded {
    ValidEmbbeded( const char *fieldName, bool (PROTO::*has)( ) const, const INNER &(PROTO::*getter)( ) const ) :
        m_fieldName( fieldName ),
        m_has( has ),
        m_getter( getter )
    {
    }

    ValidationResult operator( )( const PROTO *proto ) const {
        ValidationResult result;
        StaticTrace trace( "Starting validation of embbeded proto: " );
        trace << m_fieldName;

        result.traces.info( trace );

        if( (proto->*m_has)( ) ) {
            VALIDATOR validator;

            auto innerResult = validator.validate( *(proto->*m_getter)( ) );

            result |= innerResult;
        } else {
            result.result = false;
            result.traces.error( std::string( "Embbeded proto absent" ) );
        }

        return result;
    }

private:
    const char *m_fieldName;
    bool (PROTO::*m_has)( ) const;
    const INNER &(PROTO::*m_getter)( ) const;
};

#endif

} // namespace pbv.

#endif
