#ifndef PBV_EMBBEDED_HPP
#define PBV_EMBBEDED_HPP

#include "pbv/AsyncSupport.hpp"
#include "pbv/Evaluable.hpp"
#include "pbv/StaticTrace.hpp"

namespace pbv {

namespace details {

template< typename VALIDATOR, typename PROTO > struct AsyncValidEmbbeded : public AsyncExpression {
    using INNER = typename VALIDATOR::PROTO;

    AsyncValidEmbbeded( const char *fieldName, bool (PROTO::*has)( ) const, const INNER &(PROTO::*getter)( ) const ) :
        m_fieldName( fieldName ),
        m_has( has ),
        m_getter( getter )
    {
    }

    ValidationResult operator( )( const PROTO *proto ) const {
        ValidationResult result( (proto->*m_has)( ) );
        StaticTrace trace;

        if( result ) {
            {
                VALIDATOR validator;

                auto innerResult = validator.validate( (proto->*m_getter)( ) );

                result &= innerResult;
            }

            trace = "Embbeded proto ";
            trace << m_fieldName;
            if( result.result == true ) {
                trace << " success";
                result.traces.info( trace );
            } else {
                trace << " failled";
                result.traces.error( trace );
            }
        } else {
            trace = "Required embbeded proto ";
            trace << m_fieldName;
            trace << " empty";

            result.result = true;
            result.traces.error( trace );
        }

        return result;
    }

private:
    const char *m_fieldName;
    bool (PROTO::*m_has)( ) const;
    const INNER &(PROTO::*m_getter)( ) const;
};

template< typename VALIDATOR, typename PROTO > struct OptionallyAsyncValidEmbbeded : public AsyncExpression {
    using INNER = typename VALIDATOR::PROTO;

    OptionallyAsyncValidEmbbeded( const char *fieldName, bool (PROTO::*has)( ) const, const INNER &(PROTO::*getter)( ) const ) :
        m_fieldName( fieldName ),
        m_has( has ),
        m_getter( getter )
    {
    }

    ValidationResult operator( )( const PROTO *proto ) const {
        ValidationResult result;
        StaticTrace trace;

        if( (proto->*m_has)( ) ) {
            {
                VALIDATOR validator;

                auto innerResult = validator.validate( (proto->*m_getter)( ) );

                result |= innerResult;
            }

            trace = "Embbeded proto ";
            trace << m_fieldName;
            if( result.result == true ) {
                trace << " success";
                result.traces.info( trace );
            } else {
                trace << " failled";
                result.traces.error( trace );
            }
        } else {
            trace = "Optionally embbeded proto ";
            trace << m_fieldName;
            trace << " absent. Skip it";

            result.result = true;
            result.traces.info( trace );
        }

        return result;
    }

private:
    const char *m_fieldName;
    bool (PROTO::*m_has)( ) const;
    const INNER &(PROTO::*m_getter)( ) const;
};

} // namespace details.

template< typename VALIDATOR, typename PROTO, typename INNER = typename VALIDATOR::PROTO > Evaluable< PROTO > ValidEmbbeded( const char *fieldName, bool (PROTO::*has)( ) const, const INNER &(PROTO::*getter)( ) const ) {
    return details::AsyncValidEmbbeded< VALIDATOR, PROTO >( fieldName, has, getter );
}

template< typename VALIDATOR, typename PROTO, typename INNER = typename VALIDATOR::PROTO > Evaluable< PROTO > OptionallyValidEmbbeded( const char *fieldName, bool (PROTO::*has)( ) const, const INNER &(PROTO::*getter)( ) const ) {
    return details::OptionallyAsyncValidEmbbeded< VALIDATOR, PROTO >( fieldName, has, getter );
}

} // namespace pbv.

#endif
