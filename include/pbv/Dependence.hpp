#ifndef PBV_DEPENDENCE_HPP
#define PBV_DEPENDENCE_HPP

#include <atomic>

namespace pbv {

namespace details {

struct BasicRule;

} // namespace details.

struct Dependence {
    static constexpr int VERSION = 1;

private:
    enum Operation {
        OALWAYS = 0,
        OEVAL,
        ONEVAL,
        OEQ,
        ONE,
        OLT,
        OLE,
        OGT,
        OGE
    };

public:
    Dependence( details::BasicRule &observed ) : Dependence( observed, Operation::OEVAL ) { }

    bool isReady( ) noexcept {
        return true;
    }

    operator int( ) const noexcept {
        return m_result;
    }

    static Dependence EVAL( details::BasicRule &target ) { return Dependence( target, Operation::OEVAL ); }
    static Dependence NEVAL( details::BasicRule &target ) { return Dependence( target, Operation::ONEVAL ); }
    static Dependence EQ( details::BasicRule &target, int val ) { return Dependence( target, Operation::OEQ, val ); }
    static Dependence NE( details::BasicRule &target, int val ) { return Dependence( target, Operation::ONE, val ); }
    static Dependence LT( details::BasicRule &target, int val ) { return Dependence( target, Operation::OLT, val ); }
    static Dependence LE( details::BasicRule &target, int val ) { return Dependence( target, Operation::OLE, val ); }
    static Dependence GT( details::BasicRule &target, int val ) { return Dependence( target, Operation::OGT, val ); }
    static Dependence GE( details::BasicRule &target, int val ) { return Dependence( target, Operation::OGE, val ); }

private:
    Dependence( details::BasicRule &target, Operation oper, int val = 0 );

    bool m_result;
};

} // namespace pbv.

#endif
