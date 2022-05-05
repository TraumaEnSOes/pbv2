#ifndef PBV_TYPETRAITS_HPP
#define PBV_TYPETRAITS_HPP

#include <type_traits>

namespace pbv {

namespace details {

#if __cplusplus >= 202002L

using RemoveCVRef = std::remove_cvref;

#else
template< typename T > struct RemoveCVRef {
    using type = typename std::remove_cv_t< std::remove_reference_t< T > >;
};

#endif

template< typename T > using RemoveCVRefType = typename RemoveCVRef< T >::type;

} // namespace details.

} // namespace pbv.

#endif
