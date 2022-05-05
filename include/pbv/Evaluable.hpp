#ifndef PBV_EVALUABLE_HPP
#define PBV_EVALUABLE_HPP

#include "pbv/ValidationResult.hpp"

#include <functional>

namespace pbv {

template< typename PROTO > using Evaluable = std::function< ValidationResult( const PROTO *proto ) >;

} // namespace pbv.

#endif
