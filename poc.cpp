#include <cassert>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <type_traits>
#include <vector>

#include "include/pbv/TracesStore.hpp"

struct EvaluationResult {
    EvaluationResult( bool r = false ) : result( r ) { }
    bool result;
    pbv::TracesStore traces;
};

void WaitAll( ) { }

namespace details {

struct BaseAsyncExpression { };

template< typename T, bool V = std::is_base_of< BaseAsyncExpression, T >::value > constexpr bool IsAsyncExpression = V;

template< typename PROTO, bool V > struct FixedExpression {
    EvaluationResult operator()( const char *, const PROTO * ) const noexcept {
        std::cout << "Fixed: " << V << '\n';

        return EvaluationResult( V );
    }
};

template< typename PROTO, bool V > struct AsyncExpression : public BaseAsyncExpression {
    EvaluationResult operator()( const char *, const PROTO * ) const noexcept { return EvaluationResult( V ); }
};

template< typename PROTO > struct Expression {
    template< typename T > Expression( T &&arg ) :
        m_callable( std::move( arg ) ),
        isAsync( IsAsyncExpression< T > )
    {
    }

    EvaluationResult operator()( const char *fieldName, const PROTO *proto ) const {
        return m_callable( fieldName, proto );
    }

    std::function< EvaluationResult( const char *fieldName, const PROTO *proto ) > m_callable;
    const bool isAsync;
};

template< typename P > struct BasicRule {
    using PROTO = P;

    BasicRule( const char *msg, const PROTO &proto, Expression< PROTO > exp ) :
        m_total( 1 ),
        m_ready( exp.isAsync )
    {
        evalSingleExpression( msg, proto, std::move( exp ) );
    }

    BasicRule( bool doEval, const char *msg, const PROTO &proto, Expression< PROTO > exp ) :
        m_total( 1 )
    {
        if( doEval ) { evalSingleExpression( msg, proto, std::move( exp ) ); }
    }

    BasicRule( const char *msg, const PROTO &proto, std::initializer_list< Expression< PROTO > > expressionsList ) :
        m_total( expressionsList.size( ) )
    {
        evalRepeatedExpressions( msg, proto, expressionsList );
    }

    BasicRule( bool doEval, const char *msg, const PROTO &proto, std::initializer_list< Expression< PROTO > > expressionsList ) :
        m_total( expressionsList.size( ) )
    {
        if( doEval ) { evalRepeatedExpressions( msg, proto, expressionsList ); }
    }

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

private:
    void waitToReady( ) { }

    EvaluationResult evalSingleExpression( const char *msg, const PROTO &proto, const Expression< PROTO > &expression ) {        
        if( expression.isAsync ) { throw std::runtime_error( "Async expression not supported yet" ); }

        ++m_evaluated;
        auto result = expression( msg, &proto );

        m_success += result.result;

        m_traces.reserve( m_traces.size( ) + result.traces.size( ) );
        m_traces.insert( m_traces.end( ), result.traces.begin( ), result.traces.end( ) );

        return result;
    }

    void evalRepeatedExpressions( const char *msg, const PROTO &proto, std::initializer_list< Expression< PROTO > > expressionsList ) {
        assert( m_total );

        for( const auto &expression : expressionsList ) {
            evalSingleExpression( msg, proto, expression );
        }
    }

    int m_total;
    bool m_ready = true;
    int m_evaluated = 0;
    int m_success = 0;
    std::vector< std::string > m_traces;
};

} // namespace details.

struct Proto {

};

template< typename T > struct Validator {
    using PROTO = T;

    using BasicRule = details::BasicRule< PROTO >;
    using Expression = details::Expression< PROTO >;
};

struct ProtoValidator : public Validator< Proto > {
    EvaluationResult operator()( const Proto &proto ) const {
        AsyncPrologue( );

        BasicRule testRule( "testRule", proto, details::FixedExpression< PROTO, false >( ) );

        BasicRule testComplexRule( "testComplexRute", proto, {
            details::FixedExpression< PROTO, true >( ),
            details::FixedExpression< PROTO, false >( )
        } );

        BasicRule dependendRule( testRule, "dependendRule", proto, details::FixedExpression< PROTO, true >( ) );

        BasicRule dependendRule2( testComplexRule == 1, "dependendRule", proto, {
            details::FixedExpression< PROTO, true >( ),
            details::FixedExpression< PROTO, false >( )
        } );

        AsyncEpilogue( );

        return { 0 };
    }
};

int main( ) {
    Proto proto;
    ProtoValidator validator;

    auto result = validator( proto );

    return result.result;
}
