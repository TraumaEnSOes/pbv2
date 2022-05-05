#ifndef PBV_ASYNCSUPPORT_HPP
#define PBV_ASYNCSUPPORT_HPP

#include <type_traits>

namespace pbv {

namespace details {

struct AsyncExpression { };

template< typename T > constexpr bool IsAsyncExpression = std::is_base_of_v< AsyncExpression, T >;

} // namespace details.

inline void AsyncPrologue( ) { }

inline void AsyncEpilogue( ) { }

} // namespace pbv.

#endif
