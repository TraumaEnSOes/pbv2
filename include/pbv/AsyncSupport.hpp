#ifndef PBV_ASYNCSUPPORT_HPP
#define PBV_ASYNCSUPPORT_HPP

#include <type_traits>

namespace pbv {

namespace details {

struct AsyncExpression { };

#ifdef PBV_SUPPORT_ASYNC
template< typename T > constexpr bool IsAsyncExpression = std::is_base_of_v< AsyncExpression, T >;
#else
template< typename T > constexpr bool IsAsyncExpression = false;
#endif

} // namespace details.

inline void AsyncPrologue( ) { }

inline void AsyncEpilogue( ) { }

} // namespace pbv.

#endif
