#ifndef PBV_TRACESSTORE_HPP
#define PBV_TRACESSTORE_HPP

#include <string>
#include <vector>

namespace pbv {

enum TraceLevel {
    ERROR = 0,
    WARNING,
    INFO,
    DEBUG
};

namespace details {

struct Trace {
    Trace( TraceLevel lev, std::string txt ) :
        level( lev ),
        text( txt )
    {
    }

    TraceLevel level;
    std::string text;
};

} // namespace details.

struct TracesStore {
    TracesStore &operator+=( TracesStore other ) {
        if( !other.m_traces.empty( ) ) {
            m_traces.reserve( m_traces.size( ) + other.m_traces.size( ) );
            m_traces.insert( m_traces.end( ), other.m_traces.begin( ), other.m_traces.end( ) );
        }

        return *this;
    }

    void error( std::string msg ) {
        m_traces.push_back( details::Trace( TraceLevel::ERROR, std::move( msg ) ) );
    }

    void warning( std::string msg ) {
        m_traces.push_back( details::Trace( TraceLevel::WARNING, std::move( msg ) ) );
    }

    void info( std::string msg ) {
        m_traces.push_back( details::Trace( TraceLevel::INFO, std::move( msg ) ) );
    }

    void debug( std::string msg ) {
        m_traces.push_back( details::Trace( TraceLevel::DEBUG, std::move( msg ) ) );
    }

    auto empty( ) const noexcept { return m_traces.empty( ); }

    auto size( ) const noexcept { return m_traces.size( ); }

    auto begin( ) const noexcept { return m_traces.begin( ); }
    auto end( ) const noexcept { return m_traces.end( ); }
    auto cbegin( ) const noexcept { return m_traces.begin( ); }
    auto cend( ) const noexcept { return m_traces.end( ); }

private:
    std::vector< details::Trace > m_traces;
};

} // namespace pbv.

#endif
