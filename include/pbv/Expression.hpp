#ifndef PBV_EXPRESSION_HPP
#define PBV_EXPRESSION_HPP

#include "pbv/AsyncSupport.hpp"
#include "pbv/ValidationResult.hpp"

#include <functional>

namespace pbv {

namespace details {

template< typename PROTO > struct TemplatizedExpression {
    template< typename T > TemplatizedExpression( T &&arg ) :
        m_evaluable( std::move( arg ) ),
        isAsync( IsAsyncExpression< T > )
    {
    }

    ValidationResult operator( )( const PROTO *proto ) const {
        return m_evaluable( proto );
    }

private:
    std::function< ValidationResult( const PROTO *proto ) > m_evaluable;
    const bool isAsync;
};

} // namespace details.

} // namespace details.

#endif
