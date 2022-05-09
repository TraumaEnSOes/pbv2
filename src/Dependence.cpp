#include "pbv/Dependence.hpp"
#include "pbv/Rules.hpp"

#include <stdexcept>

namespace pbv {

Dependence::Dependence( details::BasicRule &target, Operation oper, int val ) {
    static_assert( VERSION == 1 );

    switch( oper ) {
    case OALWAYS:
        m_result = true;
        break;

    case OEVAL:
        m_result = target.evaluated( );
        break;

    case ONEVAL:
        m_result = !( target.evaluated( ) );
        break;

    case OEQ:
        m_result = ( target.success( ) == val );
        break;

    case ONE:
        m_result = ( target.success( ) != val );
        break;

    case OLT:
        m_result = ( target.success( ) < val );
        break;

    case OLE:
        m_result = ( target.success( ) <= val );
        break;

    case OGT:
        m_result = ( target.success( ) > val );
        break;

    case OGE:
        m_result = ( target.success( ) >= val );
        break;

    default:
        throw std::runtime_error( "Internal error ! Unknown Dependence operation" );
    }
}

}