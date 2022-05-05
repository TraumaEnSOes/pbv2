#ifndef PBV_STATICTRACE_HPP
#define PBV_STATICTRACE_HPP

#include <algorithm>
#include <charconv>
#include <limits>
#include <string>
#include <string_view>

namespace pbv {

namespace details {

struct DoStaticTrace {
    size_t length( ) const noexcept { return m_index; }
    size_t size( ) const noexcept { return m_index; }

    bool empty( ) const noexcept { return m_index == 0; }

    void clear( ) noexcept { m_index = 0; *m_buffer = 0; }

    operator bool( ) const noexcept { return !m_index == 0; }
    bool operator !( ) const noexcept { return m_index == 0; }

    std::string toString( ) const { return ( m_index == 0 ) ? std::string( ) : std::string( m_buffer, m_index ); }
    std::string_view toStringView( ) const { return ( m_index == 0 ) ? std::string_view( ) : std::string_view( m_buffer, m_index ); }
    const char *data( ) const noexcept { return m_buffer; }
    const char *c_str( ) const noexcept { return m_buffer; }

    operator std::string( ) const { return toString( ); }
    operator std::string_view( ) const { return toStringView( ); }
    operator const char *( ) const noexcept { return m_buffer; }

protected:
    DoStaticTrace( char *buff ) :
        m_buffer( buff )
    {
        *m_buffer = 0;
    }

    void doAppend( signed char ch ) noexcept { m_buffer[m_index] = ch; ++m_index; }
    void doAppend( unsigned char ch ) noexcept { m_buffer[m_index] = ch; ++m_index; }

    void doAppend( signed int v ) noexcept {
        auto result = std::to_chars( &( m_buffer[m_index] ), static_cast< char * >( nullptr ) + std::numeric_limits< size_t >::max( ), v );
        m_index += std::distance( m_buffer, result.ptr );
    }

    void doAppend( unsigned int v ) noexcept {
        auto result = std::to_chars( &( m_buffer[m_index] ), static_cast< char * >( nullptr ) + std::numeric_limits< size_t >::max( ), v );
        m_index += std::distance( m_buffer, result.ptr );
    }

    void doAppend( signed long long v ) noexcept {
        auto result = std::to_chars( &( m_buffer[m_index] ), static_cast< char * >( nullptr ) + std::numeric_limits< size_t >::max( ), v );
        m_index += std::distance( m_buffer, result.ptr );
    }
    void doAppend( unsigned long long v ) noexcept {
        auto result = std::to_chars( &( m_buffer[m_index] ), static_cast< char * >( nullptr ) + std::numeric_limits< size_t >::max( ), v );
        m_index += std::distance( m_buffer, result.ptr );
    }

    void doAppend( const char *str, size_t length ) noexcept {
        std::copy( str, str + length, &(m_buffer[m_index]) );
        m_index += length;
    }
    void doAppend( const char *str ) noexcept { doAppend( str, std::char_traits< char >::length( str ) ); }


    void doAssign( signed char ch ) noexcept { clear( ); doAppend( ch ); }
    void doAssign( unsigned char ch ) noexcept { clear( ); doAppend( ch ); }

    void doAssign( signed int v ) noexcept { clear( ); doAppend( v ); }
    void doAssign( unsigned int v ) noexcept { clear( ); doAppend( v ); }

    void doAssign( signed long long v ) noexcept { clear( ); doAppend( v ); }
    void doAssign( unsigned long long v ) noexcept { clear( ); doAppend( v ); }

    void doAssign( const char *str, size_t length ) noexcept { clear( ); doAppend( str, length ); }
    void doAssign( const char *str ) noexcept { clear( ); doAppend( str ); }

    void doIndex( int idx ) noexcept {
        doAppend( '[' );
        doAppend( idx );
        doAppend( ']' );
    }

private:
    char *m_buffer;
    size_t m_index = 0;
};

} // namespace details.

template< size_t SIZE > struct StaticTraceN : public details::DoStaticTrace {
    StaticTraceN( ) :
        details::DoStaticTrace( m_storage )
    {
    }
    StaticTraceN( signed char ch ) : details::DoStaticTrace( m_storage ) { doAppend( ch ); }
    StaticTraceN( unsigned char ch ) : details::DoStaticTrace( m_storage ) { doAppend( ch ); }
    StaticTraceN( signed v ) : details::DoStaticTrace( m_storage ) { doAppend( v ); }
    StaticTraceN( unsigned v ) : details::DoStaticTrace( m_storage ) { doAppend( v ); }
    StaticTraceN( signed long long v ) : details::DoStaticTrace( m_storage ) { doAppend( v ); }
    StaticTraceN( unsigned long long v ) : details::DoStaticTrace( m_storage ) { doAppend( v ); }
    StaticTraceN( const char *str ) : details::DoStaticTrace( m_storage ) { doAppend( str ); }
    StaticTraceN( const char *str, size_t length ) : details::DoStaticTrace( m_storage ) { doAppend( str, length ); }
    template< int N > StaticTraceN( const char v[N] ) : details::DoStaticTrace( m_storage ) { doAppend( v, N ); }
    StaticTraceN( const std::string &str ) : details::DoStaticTrace( m_storage ) { doAppend( str.data( ), str.length( ) ); }
    StaticTraceN( std::string_view str ) : details::DoStaticTrace( m_storage ) { doAppend( str.data( ), str.length( ) ); }


    StaticTraceN &operator=( signed char ch ) { doAssign( ch ); return *this; }
    StaticTraceN &operator=( unsigned char ch ) { doAssign( ch ); return *this; }
    StaticTraceN &operator=( signed v ) { doAssign( v ); return *this; }
    StaticTraceN &operator=( unsigned v ) { doAssign( v ); return *this; }
    StaticTraceN &operator=( signed long long v ) { doAssign( v ); return *this; }
    StaticTraceN &operator=( unsigned long long v ) { doAssign( v ); return *this; }
    StaticTraceN &operator=( const char *str ) { doAssign( str ); return *this; }
    template< int N > StaticTraceN &operator=( const char str[N] ) { doAssign( str, N ); return *this; }


    StaticTraceN &assign( signed char ch ) { doAssign( ch ); return *this; }
    StaticTraceN &assign( unsigned char ch ) { doAssign( ch ); return *this; }
    StaticTraceN &assign( signed v ) { doAssign( v ); return *this; }
    StaticTraceN &assign( unsigned v ) { doAssign( v ); return *this; }
    StaticTraceN &assign( signed long long v ) { doAssign( v ); return *this; }
    StaticTraceN &assign( unsigned long long v ) { doAssign( v ); return *this; }
    StaticTraceN &assign( const char *str, size_t length ) { doAssign( str, length ); return *this; }
    StaticTraceN &assign( const char *str ) { doAssign( str ); return *this; }
    template< int N > StaticTraceN &assign( const char str[N] ) { doAssign( str, N ); return *this; }


    constexpr size_t max_size( ) const noexcept { return SIZE; }
    constexpr size_t capacity( ) const noexcept { return SIZE; }


    StaticTraceN &operator<<( signed char ch ) noexcept { doAppend( ch ); return *this; }
    StaticTraceN &operator<<( unsigned char ch ) noexcept { doAppend( ch ); return *this; }
    StaticTraceN &operator<<( signed v ) noexcept { doAppend( v ); return *this; }
    StaticTraceN &operator<<( unsigned v ) noexcept { doAppend( v ); return *this; }
    StaticTraceN &operator<<( signed long long v ) noexcept { doAppend( v ); return *this; }
    StaticTraceN &operator<<( unsigned long long v ) noexcept { doAppend( v ); return *this; }
    StaticTraceN &operator<<( const char *str ) noexcept { doAppend( str ); return *this; }
    template< int N > StaticTraceN &operator<<( const char v[N] ) noexcept { doAppend( v ); return *this; }
    StaticTraceN &operator<<( const std::string &str ) { doAppend( str.data( ), str.length( ) ); return *this; }
    StaticTraceN &operator<<( std::string_view str ) { doAppend( str.data( ), str.length( ) ); return *this; }


    StaticTraceN &append( signed char ch ) noexcept { doAppend( ch ); return *this; }
    StaticTraceN &append( unsigned char ch ) noexcept { doAppend( ch ); return *this; }
    StaticTraceN &append( signed v ) noexcept { doAppend( v ); return *this; }
    StaticTraceN &append( unsigned v ) noexcept { doAppend( v ); return *this; }
    StaticTraceN &append( signed long long v ) noexcept { doAppend( v ); return *this; }
    StaticTraceN &append( unsigned long long v ) noexcept { doAppend( v ); return *this; }
    StaticTraceN &append( const char *str ) noexcept { doAppend( str ); return *this; }
    StaticTraceN &append( const char *str, size_t length ) noexcept { doAppend( str, length ); return *this; }
    template< int N > StaticTraceN &append( const char v[N] ) noexcept { doAppend( v, N ); return *this; }
    StaticTraceN &append( const std::string &str ) { doAppend( str.data( ), str.length( ) ); return *this; }
    StaticTraceN &append( std::string_view str ) { doAppend( str.data( ), str.length( ) ); return *this; }


    StaticTraceN &operator+=( signed char ch ) noexcept { doAppend( ch ); return *this; }
    StaticTraceN &operator+=( unsigned char ch ) noexcept { doAppend( ch ); return *this; }
    StaticTraceN &operator+=( signed v ) noexcept { doAppend( v ); return *this; }
    StaticTraceN &operator+=( unsigned v ) noexcept { doAppend( v ); return *this; }
    StaticTraceN &operator+=( signed long long v ) noexcept { doAppend( v ); return *this; }
    StaticTraceN &operator+=( unsigned long long v ) noexcept { doAppend( v ); return *this; }
    StaticTraceN &operator+=( const char *str ) noexcept { doAppend( str ); return *this; }
    template< int N > StaticTraceN &operator+=( const char v[N] ) noexcept { doAppend( v ); return *this; }
    StaticTraceN &operator+=( const std::string &str ) { doAppend( str.data( ), str.length( ) ); return *this; }
    StaticTraceN &operator+=( std::string_view str ) { doAppend( str.data( ), str.length( ) ); return *this; }


    StaticTraceN &operator( )( int idx ) noexcept { doIndex( idx ); return *this; }

private:
    char m_storage[SIZE] = { 0 };
};

using StaticTrace = StaticTraceN< 1024 >;

} // namespace pbv.

#endif
