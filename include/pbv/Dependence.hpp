#ifndef PBV_DEPENDENCE_HPP
#define PBV_DEPENDENCE_HPP

namespace pbv {

namespace details {

struct BasicRule;

} // namespace details.

struct Dependence {
private:
    enum Operation {
        ALWAYS = 0,
        EVAL = 1,
        NEVAL,
        EQ,
        NE,
        LT,
        LE,
        GT,
        GE
    };

public:
    Dependence( ) :
        m_target( *static_cast< details::BasicRule * >( nullptr ) ),
        m_operation( Operation::ALWAYS )
    {
    }

    Dependence( details::BasicRule &target ) :
        m_target( target ),
        m_operation( Operation::LE ),
        m_value( 1 )
    {
    }

    static Dependence EVAL( details::BasicRule &target ) { return Dependence( target, Operation::EVAL ); }
    static Dependence NEVAL( details::BasicRule &target ) { return Dependence( target, Operation::NEVAL ); }
    static Dependence EQ( details::BasicRule &target, int val ) { return Dependence( target, Operation::EQ, val ); }
    static Dependence NE( details::BasicRule &target, int val ) { return Dependence( target, Operation::NE, val ); }
    static Dependence LT( details::BasicRule &target, int val ) { return Dependence( target, Operation::LT, val ); }
    static Dependence LE( details::BasicRule &target, int val ) { return Dependence( target, Operation::LE, val ); }
    static Dependence GT( details::BasicRule &target, int val ) { return Dependence( target, Operation::GT, val ); }
    static Dependence GE( details::BasicRule &target, int val ) { return Dependence( target, Operation::GE, val ); }

private:
    Dependence( details::BasicRule &target, Operation oper, int val = 0 ):
        m_target( target ),
        m_operation( oper ),
        m_value( val )
    {
    }

    details::BasicRule &m_target;
    Operation m_operation;
    int m_value;
};

} // namespace pbv.

#endif
