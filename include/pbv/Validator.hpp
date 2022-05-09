#ifndef PBV_VALIDATOR_HPP
#define PBV_VALIDATOR_HPP

#include "pbv/Rules.hpp"

#include <cstddef>
#include <functional>
#include <optional>

namespace pbv {

template< typename P > struct Validator {
    using PROTO = P;

    using Optional = details::OptionalRule< PROTO >;

    virtual ~Validator( ) = default;

    ValidationResult validate( const PROTO &proto ) const {
        return doValidation( &proto );
    }

private:
    virtual ValidationResult doValidation( const PROTO *proto ) const = 0;
};

} // namespace pbv.

#endif