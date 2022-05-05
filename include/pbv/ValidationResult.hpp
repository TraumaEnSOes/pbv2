#ifndef PBV_VALIDATIONRESULT_HPP
#define PBV_VALIDATIONRESULT_HPP

#include "pbv/TracesStore.hpp"

namespace pbv {

struct ValidationResult {
    ValidationResult( bool status = false ) : result( status ) { }

    ValidationResult &operator |=( ValidationResult &other ) {
        result |= other.result;
        traces += other.traces;

        return *this;
    }

    ValidationResult &operator &=( ValidationResult &other ) {
        result |= other.result;
        traces += other.traces;

        return *this;
    }

    operator bool( ) const noexcept { return result; }
    bool operator !( ) const noexcept { return !result; }

    bool result;

    TracesStore traces;
};

} // namespace pbv.

#endif
