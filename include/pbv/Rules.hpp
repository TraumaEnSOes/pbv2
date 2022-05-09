#ifndef PBV_RULES_HPP
#define PBV_RULES_HPP

#include "pbv/Dependence.hpp"
#include "pbv/Expression.hpp"

#include <functional>
#include <initializer_list>
#include <type_traits>

namespace pbv {

namespace details {

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

    bool isReady( ) const noexcept {
#ifdef PBV_SUPPORT_ASYNC
        return m_ready.load( );
#else
        return true;
#endif
    }

protected:
    static inline void errors2Warnings( TracesStore &traces ) noexcept { traces.errors2Warnings( ); }

    void updateResults( ValidationResult &result, int evaluated = 1 );

private:
#ifdef PBV_SUPPORT_ASYNC
    void waitToReady( ) noexcept;
#else
    void waitToReady( ) noexcept { }
#endif

    int m_total;
#ifdef PBV_SUPPORT_ASYNC
    std::atomic_bool m_ready = false;
#endif
    int m_evaluated = 0;
    int m_success = 0;
    TracesStore m_traces;
    void *m_vector = nullptr;
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

    OptionalRule( Dependence &&dep, const PROTO *proto, Expression exp ) :
        BasicRule( 1 )
    {
        if( dep.isReady( ) && dep ) {
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
    void evalSingleExpression( const PROTO *proto, const Expression &exp ) {
        auto result = exp( proto );

        BasicRule::errors2Warnings( result.traces );
        BasicRule::updateResults( result );
    }

    void evalRepeatedExpressions( const PROTO *proto, ExpressionsList expsList ) {
        for( const auto &exp : expsList ) {
            evalSingleExpression( proto, exp );
        }
    }
};

} // namespace details.

} // namespace pbv.

#endif
