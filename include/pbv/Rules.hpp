#ifndef PBV_RULES_HPP
#define PBV_RULES_HPP

#include "pbv/Expression.hpp"

#include <functional>
#include <initializer_list>
#include <type_traits>

namespace pbv {

namespace details {

struct AsyncExpression;

struct BasicRule {
    BasicRule( int total ) : m_total( total ) { }

    int total( ) const noexcept { return m_total; }

    int evaluated( ) noexcept {
        waitToReady( );
        return m_evaluated;
    }

    int success( ) noexcept {
        waitToReady( );
        return m_success;
    }

    operator int( ) noexcept { return success( ); }

    const TracesStore &traces( ) noexcept {
        waitToReady( );
        return m_traces;
    }

protected:
#ifdef PBV_SUPPORT_ASYNC
    bool m_ready = false;
#endif
    int m_evaluated = 0;
    int m_success = 0;
    TracesStore m_traces;

private:
    int m_total;

#ifdef PBV_SUPPORT_ASYNC
    void waitToReady( ) noexcept;
#else
    void waitToReady( ) noexcept { }
#endif
};

template< typename P > struct OptionalRule : public details::BasicRule {
    using PROTO = P;
    using Expression = TemplatizedExpression< PROTO >;
    using ExpressionsList = std::initializer_list< Expression >;

    OptionalRule( const PROTO *proto, Expression exp ) :
        BasicRule( 1 )
    {
        evalSingleExpression( proto, std::move( exp ) );
    }

    OptionalRule( bool doEval, const PROTO *proto, Expression exp ) :
        BasicRule( 1 )
    {
        if( doEval ) {
            evalSingleExpression( proto, std::move( exp ) );
        }
    }

    OptionalRule( const PROTO *proto, ExpressionsList expsList ) :
        BasicRule( expsList.size( ) )
    {
        evalRepeatedExpressions( proto, expsList );
    }

    OptionalRule( bool doEval, const PROTO *proto, ExpressionsList expsList ) :
        BasicRule( expsList.size( ) )
    {
        if( doEval ) {
            evalRepeatedExpressions( proto, expsList );
        }
    }

private:
    void evalSingleExpression( const PROTO *proto, const Expression &exp ) { }
    void evalRepeatedExpressions( const PROTO *proto, ExpressionsList expsList ) { }
};

template< typename P > struct MandatoryRule : public details::BasicRule {
    using PROTO = P;
    using Expression = TemplatizedExpression< PROTO >;
    using ExpressionsList = std::initializer_list< Expression >;

    MandatoryRule( const PROTO *proto, Expression exp ) :
        BasicRule( 1 )
    {
        evalSingleExpression( proto, std::move( exp ) );
    }

    MandatoryRule( bool doEval, const PROTO *proto, Expression exp ) :
        BasicRule( 1 )
    {
        if( doEval ) {
            evalSingleExpression( proto, std::move( exp ) );
        }
    }

    MandatoryRule( const PROTO *proto, ExpressionsList expsList ) :
        BasicRule( expsList.size( ) )
    {
        evalRepeatedExpressions( proto, expsList );
    }

    MandatoryRule( bool doEval, const PROTO *proto, ExpressionsList expsList ) :
        BasicRule( expsList.size( ) )
    {
        if( doEval ) {
            evalRepeatedExpressions( proto, expsList );
        }
    }

private:
    void evalSingleExpression( const PROTO *proto, const Expression &exp ) { }
    void evalRepeatedExpressions( const PROTO *proto, ExpressionsList expsList ) { }
};

} // namespace details.

} // namespace pbv.

#endif
